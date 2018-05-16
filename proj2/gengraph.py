#!/usr/bin/python2
# -*- coding: utf-8 -*-
'''
    Gera grafos pesados positivos direcionados aleatórios com densidade predifinda
'''
import os
import random
from math import sqrt, log
random.seed()
testsDir = "randomTests_6"
density = 0.95
maxFdensity = 0.05
maxN = 1000
minN = 250
def C_top(N):
    #return density * N * log(N) #small
    return density * N * sqrt(N) #medium
    #return density * N * (N-1) #dense
minW = 1
maxW = 0x69
K = 100
os.system("rm -rf ./" + testsDir + "/")
os.system("mkdir ./" + testsDir + "/")

def genGraph(N, L):
    V = set()
    j = 1
    while(j != L):
        u = random.randint(1,N)
        v = u
        while (u==v):
            v = random.randint(1,N)
        if ((u,v) in V):
            continue
        V.add((u,v))
        j+=1
    V = list(V)
    W = []
    for i in V:
        w = random.randint(minW,maxW)
        W.append((V[0], V[1], w))
    return V

for i in range(K):
    if (i%(K/10)==0):
        print i, "/", K
    N = random.randint(minN,maxN+1)
    C = int(C_top(N))
    F = int(0.05*N)
    print N, F, C
    V = genGraph(N,C)

    S = random.sample(range(1, N), F)
    with open("%s/%d.in"%(testsDir,i), "w") as f:
        f.write("%d %d %d\n" % (N, F, C))
        Ss = " ".join(str(s) for s in S)
        f.write(Ss + "\n")
        for j in V:
            f.write("%d %d\n" % (j[0], j[1]))
        f.close()
