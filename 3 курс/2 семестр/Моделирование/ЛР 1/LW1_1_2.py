from math import *

def f(x):
    return exp(4*x)

def df(x, h):
    return (-3*f(x) + 4*f(x + h) - f(x + 2*h)) / (2*h)

x = 1
h = 0.1
acc = 4*exp(4*x)

print ("h                 df        error")

y = df(x, h)
err = y - acc

while True:
    print ("{0:<17} {1:3.5f} {2}".format(h, y, abs(y - acc)))

    h = h / 2
    y = df(x, h)

    if (abs(y - acc) > abs(err)):
        print ("{0:<17} {1:3.5f} {2}".format(h, y, abs(y - acc)))
        break
    
    err = y - acc

print('h_эксп.: {0}'.format(2*h))
