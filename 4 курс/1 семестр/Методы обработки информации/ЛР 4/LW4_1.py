import numpy as np
from scipy.stats import t, norm

# Заданные значения
n1 = 10
n2 = 700
q0 = 0.8
a = 1
sigma0 = 0.5

# Генерация случайных выборок с нормальным распределением
sample1 = np.random.normal(a, sigma0**2, n1)
sample2 = np.random.normal(a, sigma0**2, n2)

# Расчет доверительного интервала для случая неизвестной sigma
CI1 = t.interval(q0, n1-1, loc=np.mean(sample1), scale=np.std(sample1, ddof=1)/np.sqrt(n1))
CI2 = t.interval(q0, n2-1, loc=np.mean(sample2), scale=np.std(sample2, ddof=1)/np.sqrt(n2))

print("Доверительный интервал для выборки 1 (σ неизвестно):", CI1)
print("Доверительный интервал для выборки 2 (σ неизвестно):", CI2)

# Расчет доверительного интервала для случая известной sigma
CI1_known_sigma = norm.interval(q0, loc=np.mean(sample1), scale=sigma0/np.sqrt(n1))
CI2_known_sigma = norm.interval(q0, loc=np.mean(sample2), scale=sigma0/np.sqrt(n2))

print("Доверительный интервал для выборки 1 (σ известно):", CI1_known_sigma)
print("Доверительный интервал для выборки 2 (σ известно):", CI2_known_sigma)