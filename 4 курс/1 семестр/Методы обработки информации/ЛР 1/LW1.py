import math, random, statistics
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import chi2

v = 3
sig = 2

G = math.pi / 2

f = lambda x: x**((v - 2) / 2) / (2**(v / 2) * G * sig**v) * math.exp(-x / (2 * sig**2))

N = 10000
s = [0] * N
for i in range(N):
    for j in range(v):
        x = random.normalvariate(0, sig)
        s[i] += x**2

print("--------------Модель--------------")
print(f"Выборочное среднее значение: {statistics.fmean(s):.3f}")
print(f"Медиана: {statistics.median(s):.3f}")
print(f"Верхний квартиль: {np.percentile(s, 75):.3f}")
print(f"Нижний квартиль: {np.percentile(s, 25):.3f}")
print(f"Выборочная дисперсия: {statistics.variance(s):.3f}")
print(f"СКО: {statistics.stdev(s):.3f}")

print("--------------Теория--------------")
print(f"Выборочное среднее значение: {chi2.mean(v):.3f}")
print(f"Медиана: {chi2.median(v):.3f}")
print(f"Верхний квартиль: {chi2.cdf(0.75, v):.3f}")
print(f"Нижний квартиль: {chi2.cdf(0.25, v):.3f}")
print(f"Выборочная дисперсия: {chi2.var(v):.3f}")
print(f"СКО: {chi2.std(v):.3f}")

X = np.linspace(0, 100, 101)
Y = [f(x) * 10000 for x in X]

plt.plot(X, Y)
plt.hist(s, bins=200)
plt.show()