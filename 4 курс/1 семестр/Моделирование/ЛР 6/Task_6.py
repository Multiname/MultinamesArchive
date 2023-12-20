import numpy as np
import matplotlib.pyplot as plt

# Замените данные на свои
data = np.random.rand(1000)


def normalized_correlation_function(data, z):
    N = len(data)
    Rn = np.correlate(data, np.roll(data, -z)) / (np.std(data) * np.std(np.roll(data, -z)) * N)
    return Rn[0]


# 1. Расчет нормированной корреляционной функции для интервального сдвига z от 0 до 50
z_values = np.arange(0, 51, 1)
correlation_values = [normalized_correlation_function(data, z) for z in z_values]

# 2. Построение графика нормированной автокорреляционной функции
plt.plot(z_values, correlation_values, label='Нормированная автокорреляционная функция')
plt.xlabel('Z')
plt.ylabel('Rn')
plt.legend()
plt.show()

# 3. Расчет нормированной корреляционной функции для объема выборки N = 410
N = 740
data = np.random.rand(N)
correlation_N = normalized_correlation_function(data, z_values)

# Вывод результатов
print(f"Нормированная корреляционная функция при выборке N={N}: {correlation_N}")
