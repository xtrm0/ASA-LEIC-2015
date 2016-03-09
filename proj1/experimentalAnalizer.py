#!/usr/bin/python2
# -*- coding: utf-8 -*-
'''
    Este código serve para fazer os gráficos da análise experimental da
    complexidade do algoritmo em função de min(N,L)
'''
import os
import matplotlib.pyplot as plt
import numpy as np

if (os.system("./runTests.sh y > tmp")!=0):
    print "Error running runTests.sh!"
    os._exit(1)

with open("tmp", "r") as f:
    inp = f.read().split("$")[1].strip()

inp = inp.split("\n")[1:]

i=0
x = []
y = []
while(True):
    if(len(inp) <= i):
        break
    N = int(inp[i+1].split(":")[1].strip())
    L = int(inp[i+2].split(":")[1].strip())
    I = int(inp[i+3].split(":")[1].strip())
    x += [max(N,L)]
    y += [I]
    i+=4

#print x
#print y
plt.plot(x,y,'ro')
z = np.polyfit(x, y, 1)
print "y=mx + b: [m, b] = ", z
p = np.poly1d(z)
xp = np.linspace(min(x),max(x),1000)
plt.plot(xp, p(xp), "-")
plt.axis([0, max(x)*1.05, 0, max(y)*1.05])
plt.show()
