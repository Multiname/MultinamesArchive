import pandas as pd
import numpy as np
import statsmodels.api as sm
import matplotlib.pyplot as plt
import seaborn as sns

# Считываем данные из файла в DataFrame
data = pd.read_csv('data.csv')

# Преобразуем 'Stay_In_Current_City_Years' в числовой формат
data['Stay_In_Current_City_Years'] = data['Stay_In_Current_City_Years'].replace('4+', 4).astype(int)

# Проводим факторный анализ зависимости параметра Purchase от Occupation и Stay_In_Current_City_Years
X = data[['Occupation', 'Stay_In_Current_City_Years']]
y = data['Purchase']

# Добавляем intercept для модели
X = sm.add_constant(X)

# Создаем модель методом наименьших квадратов
model = sm.OLS(y, X).fit()

# Выводим результаты анализа
print(model.summary())

# Визуализируем степень влияния каждого параметра на число Purchase
coefficients = model.params.drop('const')
coefficients.plot(kind='bar')
plt.title('Influence of factors on Purchase')
plt.xlabel('Factors')
plt.ylabel('Coefficient')
plt.show()

# Построим график зависимости R-square от размера набора данных
r_square_values = []
data_sizes = range(50000, len(data), 50000)  # Перебираем разные размеры набора данных

for size in data_sizes:
    sample_data = data.sample(size)
    X_sample = sample_data[['Occupation', 'Stay_In_Current_City_Years']]
    y_sample = sample_data['Purchase']
    X_sample = sm.add_constant(X_sample)
    model_sample = sm.OLS(y_sample, X_sample).fit()
    r_square_values.append(model_sample.rsquared)

plt.plot(data_sizes, r_square_values)
plt.title('R-square vs Data Size')
plt.xlabel('Data Size')
plt.ylabel('R-square')
plt.show()

# Визуализируем корреляционную матрицу для всех параметров
correlation_matrix = data[['Purchase', 'Occupation', 'Stay_In_Current_City_Years']].corr()
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', fmt=".2f")
plt.title('Correlation Matrix')
plt.show()
