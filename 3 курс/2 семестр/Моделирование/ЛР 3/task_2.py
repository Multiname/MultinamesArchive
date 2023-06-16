import numpy as np
from scipy.integrate import quad
import matplotlib.pyplot as plt

# Задаем промежуток и функцию
l = 3

def f(x):
    return np.where((2 <= x) & (x <= 3), 2,
                    np.where((1 <= x) & (x < 2), 3,
                             np.where((0 <= x) & (x < 1), 4, 0)))

# Вычисляем коэффициенты
a0 = 2/l * (quad(f, 0, l))[0]

def an(n): return 2/l * (quad(lambda x: f(x)
                              * np.cos(n * np.pi * x / l), 0, l))[0]

N = 100  # Количество гармоник для вычисления ряда Фурье
a = np.zeros(N+1)
for n in range(1, N+1):
    a[n] = an(n)

x = np.linspace(0, l, 1000)

# График функции f(x)
plt.plot(x, [f(i) for i in x], 'b')

# График суммы ряда Фурье
fourier = a0/2 + sum([a[n] * np.cos(n * np.pi * x / l)
                      for n in range(1, N+1)])
plt.plot(x, fourier, 'r')

plt.legend(['f(x)', 'Фурье'])
plt.show()

res = a0/2 + sum([a[n] * np.cos(n * np.pi) for n in range(1, N+1)])
print(res)
