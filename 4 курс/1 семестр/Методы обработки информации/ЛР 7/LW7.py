import numpy as np
from scipy.stats import geom, kstest, cramervonmises, chi2, chisquare

# Загрузка данных из CSV файла
with open("Test7.csv", "r") as file:
    data = file.read().splitlines()
    sample = np.array(data).astype(float)

# Уровни значимости
alpha = [0.01, 0.05, 0.1]

# Проверка гипотезы для разных объемов выборки
k1 = 8  # значение объема выборки k1
k2 = len(sample)

# Проверка гипотезы с помощью критерия Колмогорова
_, ks_p_value_k1 = kstest(sample[:k1], geom.cdf, args=(1,))
_, ks_p_value_k2 = kstest(sample, geom.cdf, args=(1,))

# Проверка гипотезы с помощью критерия Крамера - фон Мизеса
cvm_p_value_k1 = cramervonmises(sample[:k1], geom.cdf, args=(1,)).pvalue
cvm_p_value_k2 = cramervonmises(sample, geom.cdf, args=(1,)).pvalue

# Проверка гипотезы с помощью критерия Пирсона
_, chi2_p_value_k1 = chisquare(sample[:k1].astype(float))
_, chi2_p_value_k2 = chisquare(sample.astype(float))

for a in alpha:
    print(f"alpha = {a}")
    print(f"k1 = {k1}")
    print("Критерий Колмогоровa:\t\t", end='')
    if (ks_p_value_k1 <= a):
        print("Основная гипотеза H0 отвергается")
    else:
        print("Основная гипотеза H0 принимается")

    print("Критерий Крамера-фон Мизеса:\t", end='')
    if (cvm_p_value_k1 <= a):
        print("Основная гипотеза H0 отвергается")
    else:
        print("Основная гипотеза H0 принимается")

    print("Критерий Хи-квадрат:\t\t", end='')
    if (chi2_p_value_k1 <= a):
        print("Основная гипотеза H0 отвергается")
    else:
        print("Основная гипотеза H0 принимается")

    print()
    print(f"k2 = {k2}")
    print("Критерий Колмогорова:\t\t", end='')
    if (ks_p_value_k2 <= a):
        print("Основная гипотеза H0 отвергается")
    else:
        print("Основная гипотеза H0 принимается")

    print("Критерий Крамера-фон Мизеса:\t", end='')
    if (cvm_p_value_k2 <= a):
        print("Основная гипотеза H0 отвергается")
    else:
        print("Основная гипотеза H0 принимается")

    print("Критерий Хи-квадрат:\t\t", end='')
    if (chi2_p_value_k2 <= a):
        print("Основная гипотеза H0 отвергается")
    else:
        print("Основная гипотеза H0 принимается")
    print()