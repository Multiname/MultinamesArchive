import numpy as np
from scipy.integrate import quad
import matplotlib.pyplot as plt

# Задаем промежуток и функцию
l = np.pi

def f(x):
    return np.where((0 <= x) & (x <= np.pi), 0,
                    np.where((-np.pi <= x) & (x < 0), x**2, 0))

# Вычисляем коэффициенты
a0 = 1/l * (quad(f, -l, l))[0]

def an(n): return 1/l * (quad(lambda x: f(x)
                              * np.cos(n * np.pi * x / l), -l, l))[0]

def bn(n): return 1/l * (quad(lambda x: f(x)
                              * np.sin(n * np.pi * x / l), -l, l))[0]

N = 100  # Количество гармоник для вычисления ряда Фурье
a = np.zeros(N+1)
b = np.zeros(N+1)
for n in range(1, N+1):
    a[n] = an(n)
    b[n] = bn(n)

x = np.linspace(-l, l, 1000)

# График функции f(x)
plt.plot(x, [f(i) for i in x], 'b')

# График суммы ряда Фурье
fourier = a0/2 + sum([a[n] * np.cos(n * np.pi * x / l) +
                     b[n] * np.sin(n * np.pi * x / l) for n in range(1, N+1)])
plt.plot(x, fourier, 'r')

# График частичной суммы S1(x)
s1 = a0/2 + sum([a[n] * np.cos(n * np.pi * x / l) + b[n] *
                np.sin(n * np.pi * x / l) for n in range(1, 2)])
plt.plot(x, s1, 'g')

# График частичной суммы S2(x)
s2 = a0/2 + sum([a[n] * np.cos(n * np.pi * x / l) + b[n] *
                np.sin(n * np.pi * x / l) for n in range(1, 3)])
plt.plot(x, s2, 'c')

# График частичной суммы S3(x)
s3 = a0/2 + sum([a[n] * np.cos(n * np.pi * x / l) + b[n] *
                np.sin(n * np.pi * x / l) for n in range(1, 4)])
plt.plot(x, s3, 'm')

plt.legend(['f(x)', 'Фурье', 'S1(x)', 'S2(x)', 'S3(x)'])
plt.show()

# Вычисляем тригонометрический полином третьего порядка
f_approx = a0/2 + a[1] * np.cos(np.pi * x / l) + b[1] * np.sin(np.pi * x / l) + \
    a[2] * np.cos(2 * np.pi * x / l) + b[2] * np.sin(2 * np.pi * x / l) + \
    a[3] * np.cos(3 * np.pi * x / l) + b[3] * np.sin(3 * np.pi * x / l)

# Вычисляем среднее квадратичное отклонение
mse = np.sqrt(np.mean((f(x) - f_approx)**2))

print("Среднее квадратичное отклонение:", mse)
