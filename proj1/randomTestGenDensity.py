#!/usr/bin/python2
# -*- coding: utf-8 -*-
'''
    Gera grafos aleatórios com densidade predifinda
'''
import os
import random
random.seed()
testsDir = "randomTests_1.0"
density = 1
maxN = 1000
minN = int(2/density) + 2
K = 1000
os.system("rm -rf ./" + testsDir + "/")
os.system("mkdir ./" + testsDir + "/")

#Isto não fica muito lento para densidades grandes devido ao birthday paradox
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
    L = int(density * N * (N-1) / 2)
    print N, L
    V = genGraph(N,L)

    with open("%s/%d.in"%(testsDir,i), "w") as f:
        f.write("%d %d\n" % (N, L))
        for j in V:
            f.write("%d %d\n" % (j[0], j[1]))
        f.close()
