#!/usr/bin/python2
# -*- coding: utf-8 -*-
'''
    Este código serve para fazer os gráficos da análise experimental da
    complexidade do algoritmo em função de max(N,L)
'''
import os
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats

def latex_float(f):
    float_str = "{0:.3g}".format(f)
    if "e" in float_str:
        base, exponent = float_str.split("e")
        return r"{0}\times10^{{{1}}}".format(base, int(exponent))
    else:
        return float_str

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
    x += [N+L]
    y += [I]
    i+=4

#print x
#print y
plt.plot(x,y,'ro')
z = np.polyfit(x, y, 1)
st = stats.linregress(x,y)
print "y=mx + b: [m, b] =", z
print "r**2 =", st[2]**2
p = np.poly1d(z)
xp = np.linspace(min(x),max(x),1000)
plt.plot(xp, p(xp), "-")
plt.axis([0, max(x)*1.05, 0, max(y)*1.05])
plt.xlabel("N+L")
plt.ylabel(u"Instruções x86")
plt.title(r"$\sigma = 100\%$")
plt.text(0.5e4,4e8,"$r^2 = %.6f$\n $I = %s(N+L) + %s$"%(st[2]**2, latex_float(st[0]), latex_float(st[1])))
plt.show()
