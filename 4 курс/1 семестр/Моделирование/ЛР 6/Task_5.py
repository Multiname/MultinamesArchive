import numpy as np
from scipy.stats import kstest

# Функция для генерации выборки случайных чисел по линейному конгруэнтному методу
def generate_random_nums(n):
    m = 2**32
    a = 1103515245
    c = 12345
    x = 0
    nums = []
    for _ in range(n):
        x = (a * x + c) % m
        nums.append(x)
    return np.array(nums) / m

# Размеры выборок
sizes = [100, 500, 1000]

for size in sizes:
    # Генерация выборки случайных чисел по линейному конгруэнтному методу
    sample = generate_random_nums(size)
    
    # Проверка гипотезы с помощью критерия Колмогорова-Смирнова
    _, p_value = kstest(sample, 'uniform')
    
    print(f"Размер выборки: {size}")
    print(f"p-value: {p_value}")
    if p_value > 0.05:
        print("Основная гипотеза H0 принимается")
    else:
        print("Основная гипотеза H0 отвергается")
    print()