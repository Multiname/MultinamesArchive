import math
import numpy as np
import sympy as sp
from prettytable import PrettyTable
from functools import lru_cache

def interpolate_Newton_polynom(sym_x, x, fdd):
    n = len(x)
    p = fdd[0, 0]
    for k in range(1, n):
        newton = 1
        for m in range(k):
            newton *= (sym_x - x[m])
        p += newton * fdd[k, 0]
    return p

def second_derivative_oh2(func, x: list, x0):
    i = x.index(x0)
    derivative = (func(x[i+1]) - 2*func(x[i]) + func(x[i-1])) / (x[i] - x[i-1])**2
    return derivative

def function(x):
    return math.e**(4*x)

@lru_cache()
def analite_second_derivative(x):
    return 16 * math.e**(4*x)

if __name__ == "__main__":
    count = 11
    x = [round(i,1) for i in np.linspace(0, 1.0, count)]
    y = [function(i) for i in x]
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
    p = interpolate_Newton_polynom(sym_x, x, fdd)
    p = sp.simplify(p)
    print("Newton polynom: ", p, '\n')
    print("f''= ", p.diff(sym_x, 2), '\n')
    x0 = 0.6
    print("x0= ", x0)
    print("Exact value= ", analite_second_derivative(x0))
    print("Newton value= ", p.diff(sym_x, 2).subs(sym_x, x0))
    print("Inaccuraty= ", abs(analite_second_derivative(x0) - p.diff(sym_x, 2).subs(sym_x, x0)))
    print("Approximate value= ", second_derivative_oh2(function, x, x0))
    print("Inaccuraty= ", abs(analite_second_derivative(x0) - second_derivative_oh2(function, x, x0)))
