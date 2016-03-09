#!/usr/bin/python2
# -*- coding: utf-8 -*-
import os
import random
random.seed()
testsDir = "randomTests"
maxN = 5000
maxL = 1000000
minN = 2
minL = 0
count = 100
os.system("rm -rf ./randomTests/")
os.system("mkdir ./randomTests/")

for i in range(count):
    if (i%(count/10)==0):
        print i, "/", count
    N = random.randint(minN,maxN+1)
    factr = (N*(N-1)/2)
    L = random.randint(min(minL,factr-1),min(maxL, factr))
    V = []
    for j in range(1, N+1):
        for k in range(j+1, N+1):
            V.append((j,k))
    random.shuffle(V)
    V = V[0:L]

    with open("%s/%d.in"%(testsDir,i), "w") as f:
        f.write("%d %d\n" % (N, L))
        for j in V:
            f.write("%d %d\n" % (j[0], j[1]))
        f.close()
