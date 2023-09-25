import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm, gaussian_kde
import pandas as pd
from prettytable import PrettyTable

data = pd.read_csv('Test7.csv', header=None)
values = data.iloc[:, 0]
num_bins = 8

# Гистограмма и полигон приведенных частот
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.hist(values, bins=num_bins, density=True, alpha=0.6, label='Гистограмма')

hist, bin_edges = np.histogram(values, bins=num_bins, density=True, range=(values.min(), values.max()))
bin_centers = (bin_edges[:-1] + bin_edges[1:]) / 2
plt.plot(bin_centers, hist, marker='o', linestyle='-', label='Полигон')
plt.title("Гистограмма и полигон частот")
plt.legend()

edges = [(round(bin_edges[i], 2), round(bin_edges[i + 1], 2)) for i in range(num_bins)]

table = PrettyTable()
table.add_column("#", [i for i in range(1, num_bins + 1)])
table.add_column("Промежуток", edges)
table.add_column("Максимальное значение в этой точке", list(map(lambda value: round(value, 4), hist)))
table.add_column("Центр промежутка", list(map(lambda center: round(center, 2), bin_centers)))
print(table)

# Графики оценок плотности вероятности
plt.subplot(1, 2, 2)
x = np.linspace(values.min(), values.max(), 100)
plt.plot(x, norm.pdf(x, loc=values.mean(), scale=values.std()), label='Параметрическая оценка')
kde = gaussian_kde(values)
plt.plot(x, kde(x), label='Усредненная ядерная оценка')

hist_estimate = hist / (bin_centers[1] - bin_centers[0])
plt.plot(bin_centers, hist_estimate, label='Гистограммная оценка')

plt.legend()
plt.title('Графики оценок плотности вероятности')

# Находим выборочные характеристики положения и рассеивания
mean_value = np.mean(values)
median_value = np.median(values)
variance = np.var(values)
std_deviation = np.std(values)

print(f"Выборочное среднее: {mean_value:.4f}")
print(f"Выборочная медиана: {median_value:.4f}")
print(f"Выборочная дисперсия: {variance:.4f}")
print(f"Выборочное стандартное отклонение: {std_deviation}")

# Значения оценок в средних точках промежутков
parametric_estimate = norm.pdf(bin_centers, loc=values.mean(), scale=values.std())
kde_estimate = kde(bin_centers)

table = PrettyTable()
table.add_column("№", [i for i in range(1, num_bins + 1)])
table.add_column("Центр промежутков", bin_centers)
table.add_column("Гистограммная оценка плотности вероятности", hist_estimate)
table.add_column("Усредненную ядерную оценку плотности вероятности", kde_estimate)
table.add_column("Параметрическая oцeнка плотности вероятности", parametric_estimate)
print("Значения оценок в средних точках:")
print(table)

table = PrettyTable()
table.add_column("№", [i for i in range(1, num_bins + 1)])
table.add_column("Центр промежутков", bin_centers)
mse_parametric = (parametric_estimate - hist_estimate) ** 2
mse_kde = (kde_estimate - hist_estimate) ** 2
table.add_column("(Усредненная яд. оц. - Гистограммная оц.)^2", mse_parametric)
table.add_column("(Параметрическая оц. - Гистограммная оц.)^2", mse_kde)
table.add_row(['', '', 'sum', 'sum'])
table.add_row(['', '', sum(mse_parametric), sum(mse_kde)])
print(table)

# Анализ близости оценок
print(f"Среднее квадратичное отклонение параметрической оценки от гистограммной оценки: {np.sqrt(np.mean(mse_parametric)):.4f}")
print(f"Среднее квадратичное отклонение усредненной ядерной оценки от гистограммной оценки: {np.sqrt(np.mean(mse_kde)):.4f}")

plt.tight_layout()
plt.show()