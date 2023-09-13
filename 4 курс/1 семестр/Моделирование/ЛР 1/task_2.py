import math, numpy
import matplotlib.pyplot as plt

f = lambda x: math.cos(math.exp(x))
x_1 = 1
x_2 = 2
vareps = 10**-6

eps = 0.01
l = 2*vareps

def Fibonacci(f):
    a = x_1
    b = x_2
    F_x = (b - a)/l

    F = [1, 1]
    while F[-1] < F_x:
        F.append(F[-1] + F[-2])
    n = len(F) - 1

    lmb = a + F[-3] / F[-1] * (b - a)
    mu = a + F[-2] / F[-1] * (b - a)
    k = 0

    while k != n - 2:
        k += 1
        if f(lmb) > f(mu):
            a = lmb
            lmb = mu
            mu = a + F[-k-2] / F[-k-1] * (b - a)
        else:
            b = mu
            mu = lmb
            lmb = a + F[-k-3] / F[-k-1] * (b - a)

    mu = lmb + eps
    if f(lmb) == f(mu):
        a = lmb
    else:
        b = mu

    print(f"n = {n}")
    return (a + b) / 2

x_min = Fibonacci(f)
print(f"x = {x_min:.6f}; f(x) = {f(x_min):.6f}")
x_max = Fibonacci(lambda x: -f(x))
print(f"x = {x_max:.6f}; f(x) = {f(x_max):.6f}")

X = numpy.linspace(x_1, x_2, (x_2-x_1)*100)
Y = [f(x) for x in X]
plt.plot(X, Y)

plt.plot(x_min, f(x_min), 'go', label='Минимум функции')
plt.plot(x_max, f(x_max), 'ro', label='Максимум функции')
plt.legend()

plt.show()