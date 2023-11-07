import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
import csv
from prettytable import PrettyTable

def read_csv(filename):
    array = []
    with open(filename,encoding='utf-8') as read_f:
        file_reader = csv.reader(read_f)
        for row in file_reader:
            array.append(float(row[0]))
    return array

def main(array):
    sample_size = len(array)

    sample_mean = np.mean(array)
    sample_std = np.std(array)

    null_hypothesis_mean = sample_mean - 1
    t_statistic = (sample_mean - null_hypothesis_mean) / (sample_std / np.sqrt(sample_size))

    p_value = 2 * (1 - stats.t.cdf(np.abs(t_statistic), df=sample_size - 1))
    if p_value < alpha:
        print("Отвергаем нулевую гипотезу")
    else:
        print("Принимаем нулевую гипотезу")
    alternative_hypothesis_means = np.linspace(null_hypothesis_mean, null_hypothesis_mean + 5, 5)

    power_values = [
        1 - stats.t.cdf((null_hypothesis_mean - alt_mean) / (sample_std / np.sqrt(sample_size)), df=sample_size - 1)
        for alt_mean in alternative_hypothesis_means
    ]

    plt.figure()
    plt.plot(alternative_hypothesis_means, power_values)
    plt.xlabel("Значение альтернативной гипотезы")
    plt.ylabel("Мощность критерия")
    plt.title("График мощности критерия")
    plt.axhline(alpha, color='red', linestyle='--', label=f"Уровень значимости ({alpha})")
    plt.legend()
    plt.show()
    print(p_value)
    print(power_values)

    table = PrettyTable()
    table.add_column("Значение параметра распределения", alternative_hypothesis_means)
    table.add_column("Мощность теста", power_values)
    table.add_column("Ошибка 2 рода", [1 - power_values[i] for i in range(len(power_values))])
    print(table)
array = read_csv("Test7.csv")
alpha = 0.1

main(array)
main(array[:25])
