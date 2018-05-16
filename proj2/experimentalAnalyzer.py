#!/usr/bin/python2
# -*- coding: utf-8 -*-
'''
    Este código serve para fazer os gráficos da análise experimental da
    complexidade do algoritmo em função de #TODO
'''
import os
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats
from math import log

def latex_float(f):
    float_str = "{0:.3g}".format(f)
    if "e" in float_str:
        base, exponent = float_str.split("e")
        return r"{0}\times10^{{{1}}}".format(base, int(exponent))
    else:
        return float_str

if (os.system("./runTests.sh y > tmp2")!=0):
    print "Error running runTests.sh!"
    os._exit(1)

with open("tmp2", "r") as f:
    inp = f.read().split("$")[1].strip()

inp = inp.split("\n")[1:]

i=0
x = []
y = []
while(True):
    if(len(inp) <= i):
        break
    N = int(inp[i+1].split(":")[1].strip())
    F = int(inp[i+2].split(":")[1].strip())
    C = int(inp[i+3].split(":")[1].strip())
    I = int(inp[i+4].split(":")[1].strip())
    x += [N*C+F*(C+N*log(N))]
    #x += [N*C+F*((C+N)*log(N))]
    y += [I]
    i+=5

w = zip(x,y)
w.sort()
x2 = []
y2 = []
step = 10
for i in xrange(6,len(w)/step):
    mx =0
    my =0
    for j in range(0,step):
        if (w[i*step+j][1]>my):
            mx = w[i*step+j][0]
            my = w[i*step+j][1]
    x2 += [mx]
    y2 += [my]

print len(x)
#print x
#print y
plt.plot(x,y,'ro')
z = np.polyfit(x, y, 1)
z2 = np.polyfit(x2, y2, 1)
st = stats.linregress(x,y)
st2 = stats.linregress(x2,y2)
print "y=mx + b: [m, b] =", z
print "r**2 =", st[2]**2
p = np.poly1d(z)
p2 = np.poly1d(z2)
xp = np.linspace(min(x),max(x),1000)
xp2 = np.linspace(min(x2),max(x2),1000)
plt.plot(xp, p(xp), "-")
plt.plot(xp2, p2(xp2), "-")
plt.axis([0, max(x)*1.05, 0, max(y)*1.05])
#plt.xlabel(r"$NC+F((C+N)log(N))$")
plt.xlabel(r"$NC+F(C+Nlog(N))$")
plt.ylabel(u"Instruções x86")
#plt.title("Complexidade Binary Heap")
plt.title("Complexidade Fib Heap")
#plt.text(0.5e4,1.8e9,"$I = %s (NC+F((C+N)log(N))) + %s$"%(latex_float(st2[0]), latex_float(st2[1])))
#plt.text(0.5e4,1.5e9,"$I = %s (NC+F((C+N)log(N))) + %s$\n$r^2 = %.6f$"%(latex_float(st[0]), latex_float(st[1]), st[2]**2))
plt.text(0.5e4,1.8e9,"$I = %s (NC+F(C+Nlog(N))) + %s$"%(latex_float(st2[0]), latex_float(st2[1])))
plt.text(0.5e4,1.5e9,"$I = %s (NC+F(C+Nlog(N))) + %s$\n$r^2 = %.6f$"%(latex_float(st[0]), latex_float(st[1]), st[2]**2))
plt.show()
