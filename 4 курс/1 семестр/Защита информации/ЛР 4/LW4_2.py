import math

def fast_pow(x, y):
    if y == 0:
        return 1
    if y == -1:
        return 1. / x
    p = fast_pow(x, y // 2)
    p *= p
    if y % 2:
        p *= x
    return p

def reverse_element(f, d):
    X = [1, 0, f]
    Y = [0, 1, d]
    while True:
        if Y[2] == 0:
            print("Error")
            return
        elif Y[2] == 1:
            return Y[1]
        else:
            q = X[2]//Y[2]
            t = [0, 0, 0]
            for i in range(0, 3):
                t[i] = X[i] - q*Y[i]
                X[i] = Y[i]
                Y[i] = t[i]

p = 23
g = 5
x = 14
k = 17
m = 14
y = math.pow(g, x) % p
a = math.pow(g, k) % p
f = p - 1

kr = reverse_element(f, k)
b = (kr * (m - x * a)) % f

if ((fast_pow(y, a)*fast_pow(a, b)) % p) == (fast_pow(g, m) % p):
    print("Success")
else:
    print("Failed")
