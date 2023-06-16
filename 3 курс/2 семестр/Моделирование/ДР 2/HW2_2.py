import matplotlib.pyplot as plt
import numpy as np
import math

def U(x, t):
    pi = math.pi
    repetitions = 1
    r = 0.0
    for i in range(repetitions):
        n = i + 1

        temp = -(88*n*np.cos(pi*n)*(16*n**2*np.sin(5*t) - 5*np.cos(5*t) + 5*np.exp(-16*n**2*t))) \
            / (pi*(4*n**2 - 81)*(256*n**4 + 25))
        temp *= np.sin(2*n*x)

        r += temp

    return r

t = [0.0, 0.3, 1.2, 1.4]
color = ['g-', 'b-', 'r-', 'c-']
indx = 0
for tt in t:
     x = np.linspace(0, math.pi/2, num=200)
     y = []
     for i in x:
        y.append(U(i, tt))
     plt.plot(x, y, '%s' % color[indx], linewidth=2, label='t = %.2f '% tt)
     indx+=1
plt.xlabel('x')
plt.ylabel('U(x, t)')
plt.grid(True)
plt.legend(loc=0)
plt.show()