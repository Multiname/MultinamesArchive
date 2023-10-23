import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import t, norm

n1 = 10
n2 = 700
sigma0 = 0.5

q_values = np.linspace(0.01, 0.99, 50)  # 50 значений q от 0.01 до 0.99

length_CI1_unknown_sigma = []
length_CI2_unknown_sigma = []
length_CI1_known_sigma = []
length_CI2_known_sigma = []

for q in q_values:
    # Расчет доверительных интервалов для случая неизвестной sigma
    CI1_unknown_sigma = t.interval(q, n1-1, loc=0, scale=1)
    CI2_unknown_sigma = t.interval(q, n2-1, loc=0, scale=1)

    CI1_known_sigma = norm.interval(q, loc=0, scale=sigma0 / np.sqrt(n1))
    CI2_known_sigma = norm.interval(q, loc=0, scale=sigma0 / np.sqrt(n2))
    
    # Расчет длины доверительного интервала для каждого случая
    length1_unknown_sigma = CI1_unknown_sigma[1] - CI1_unknown_sigma[0]
    length2_unknown_sigma = CI2_unknown_sigma[1] - CI2_unknown_sigma[0]
    length1_known_sigma = CI1_known_sigma[1] - CI1_known_sigma[0]
    length2_known_sigma = CI2_known_sigma[1] - CI2_known_sigma[0]
    
    length_CI1_unknown_sigma.append(length1_unknown_sigma)
    length_CI2_unknown_sigma.append(length2_unknown_sigma)
    length_CI1_known_sigma.append(length1_known_sigma)
    length_CI2_known_sigma.append(length2_known_sigma)

# Построение графиков
plt.plot(q_values, length_CI1_unknown_sigma, label="n1, σ unknown")
plt.plot(q_values, length_CI2_unknown_sigma, label="n2, σ unknown")
plt.plot(q_values, length_CI1_known_sigma, label="n1, σ known")
plt.plot(q_values, length_CI2_known_sigma, label="n2, σ known")

plt.xlabel('Уровень доверия, q')
plt.ylabel('Длина доверительного интервала')
plt.title('График зависимости длины доверительного\n интервала от уровня доверия')
plt.legend()
plt.show()