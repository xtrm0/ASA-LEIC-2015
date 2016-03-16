#!/usr/bin/python2
# -*- coding: utf-8 -*-
'''
    Gera grafos aleatórios com base em intervalos para N e L
'''
import os
import random
random.seed()
testsDir = "randomTests"
maxN = 1000
maxL = 10000000
minN = 2
minL = 0
K = 1000
os.system("rm -rf ./" + testsDir + "/")
os.system("mkdir ./" + testsDir + "/")


def genGraph(N, L):
    V = set()
    for i in range(1,N):
        V.add((i,i+1))
    j = N - 1
    while(j != L):
        u = random.randint(1,N)
        v = u
        while (u==v):
            v = random.randint(1,N)
        if ((u,v) in V or (v,u) in V):
            continue
        V.add((u,v))
        j+=1
    V = list(V)
    rev = [i+1 for i in range(N)]
    random.shuffle(rev)
    for i in range(len(V)):
        V[i] = (rev[V[i][0]-1], rev[V[i][1]-1])
    return V

for i in range(K):
    if (i%(K/10)==0):
        print i, "/", K
    N = random.randint(minN,maxN+1)
    factr = (N*(N-1)/2)
    L_left  = max(min(minL,factr), N-1)
    L_rigth = max(min(maxL, factr), N-1)
    L = random.randint(L_left, L_rigth)
    print N, L
    V = genGraph(N,L)

    with open("%s/%d.in"%(testsDir,i), "w") as f:
        f.write("%d %d\n" % (N, L))
        for j in V:
            f.write("%d %d\n" % (j[0], j[1]))
        f.close()
