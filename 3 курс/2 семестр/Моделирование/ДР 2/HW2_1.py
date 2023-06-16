import matplotlib.pyplot as plt
import numpy as np
import math

def U(x, t):
    pi = np.pi
    r = 1/2*(11*math.sin(pi*(x - 8*t)) + 4*(math.cos(pi*(x - 8*t)) - 1)) + \
        1/2*(11*math.sin(pi*(x + 8*t)) - 4*(math.cos(pi*(x + 8*t)) - 1))
    
    print("r=",r)
    print(2/math.pi+t, "\n")
    return r

l = 6
a = 8

t = [0.0, 0.31, 0.61, 0.69, 0.79]
color = ['g-', 'b-', 'r-', 'c-', 'y-']
indx = 0
for tt in t:
     x = np.linspace(0, 1.1, num=200)
     print("x=",x)
     y = []
     print("tt=",tt)
     for i in x:
        y.append(U(i, tt))
     plt.plot(x, y, '%s' % color[indx], linewidth=2, label='t = %.1f '% tt)
     indx+=1
plt.xlabel('x')
plt.ylabel('U(x, t)')
plt.grid(True)
plt.legend(loc=0)
plt.show()