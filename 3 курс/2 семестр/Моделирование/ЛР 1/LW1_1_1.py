import numpy
import math
from prettytable import PrettyTable

def first_derivative_oh(func, x: list, n: int):
    derivative = n * [None]
    derivative[0] = round((func(x[1]) - func(x[0])) / (x[1] - x[0]))
    for i in range(1, n):
        derivative[i] = round( (func(x[i]) - func(x[i-1])) / (x[i] - x[i-1]), 3)
    return derivative

def first_derivative_oh2(func, x: list, n: int):
    derivative = n * [None]
    derivative[0] = round( (4*func(x[1]) - 3*func(x[0]) - func(x[2])) / (x[1] - x[0]) / 2, 3)
    derivative[1] = round( (4*func(x[2]) - 3*func(x[1]) - func(x[3])) / (x[2] - x[1]) / 2, 3)
    for i in range(2, n):
        derivative[i] = round( (3*func(x[i]) - 4*func(x[i-1]) + func(x[i-2])) / (x[i] - x[i-1]) / 2, 3)
    return derivative

def second_derivative_oh2(func, x: list, n: int):
    derivative = n * [None]
    for i in range(1, n-1):
        derivative[i] = round( (func(x[i+1]) - 2*func(x[i]) + func(x[i-1])) / (x[i] - x[i-1])**2, 3)
    return derivative

def calculate_inaccuraty(first: list, second: list):
    if len(first) != len(second):
        return [0]
    inacuraty = len(first) * [0];
    for i in range(0, len(first)):
        if first[i] is None or second[i] is None:
            inacuraty[i] = None
        else:
            inacuraty[i] = round(abs(first[i] - second[i]), 3)
    return inacuraty


def f(x):
    return math.e**(4*x)

def analite_first_derivative(x):
    return 4 * math.e**(4*x)

def analite_second_derivative(x):
    return 16 * math.e**(4*x)

if __name__ == "__main__":
    count = 11
    x = [round(i, 3) for i in numpy.linspace(0, 1, count)]
    y = [round(f(i), 3) for i in x]
    first_derivative = [round(analite_first_derivative(i), 3) for i in x]
    second_derivative = [round(analite_second_derivative(i), 3) for i in x]
    fd1 = first_derivative_oh(f, x, len(x))
    fd2 = first_derivative_oh2(f, x, len(x))
    sd2 = second_derivative_oh2(f, x, len(x))
    table = PrettyTable()
    table.add_column("x", x, "r")
    table.add_column("f(x)", y, "r")
    table.add_column("f'(x)", first_derivative, "r")
    table.add_column("f~'", fd1, "r")
    table.add_column("O(h)", calculate_inaccuraty(fd1, first_derivative), "r")
    table.add_column("f~~'", fd2, "r")
    table.add_column("O(h^2)", calculate_inaccuraty(fd2, first_derivative), "r")
    table.add_column("f''(x)", second_derivative, "r")
    table.add_column("f~''", sd2, "r")
    table.add_column("O(h^2)", calculate_inaccuraty(sd2, second_derivative), "r")
    print(table)

