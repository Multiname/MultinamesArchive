import sympy
import math
import numpy as np
import sympy as sp
from prettytable import PrettyTable

def newton(sym_x, x, fdd):
    n = len(x)
    p = fdd[0, 0]
    for k in range(1, n):
        newton = 1
        for m in range(k):
            newton *= (sym_x - x[m])
        p += newton * fdd[k, 0]
    return p

def f(x):
    return math.e**(4*x)

def ddf(x):
    return 16 * math.e**(4*x)

if __name__ == "__main__":
    count = 11
    x = [round(i,1) for i in np.linspace(0, 1.0, count)]
    y = [round(f(i), 3) for i in x]
    table = PrettyTable()
    table.add_column("x", x, "l")
    table.add_column("y", y, "l")
    print(table)
    n = len(x)
    fdd = np.asmatrix(np.zeros((n, n)))
    for i in range(n):
        fdd[0, i] = y[i]
    for j in range(1,n):
        for i in range(n-j):
            fdd[j, i] = (fdd[j-1, i+1] - fdd[j-1, i]) / (x[i+j] - x[i])
    sym_x = sp.Symbol("x")
    p = newton(sym_x, x, fdd)
    p = sp.simplify(p)
    print("Newton polynom:", p, '\n')
    print("f'':", p.diff(sym_x, 2), '\n')
    x0 = 1
    print("xn =", x0)
    print("Accurate:", ddf(x0))
    print("Newton:", p.diff(sym_x, 2).subs(sym_x, x0))
    print("Error:", abs(ddf(x0) - p.diff(sym_x, 2).subs(sym_x, x0)))
