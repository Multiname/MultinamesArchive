import matplotlib.pyplot as plt
from sklearn.datasets import fetch_openml
from sklearn.linear_model import LinearRegression

# Загрузка данных
boston = fetch_openml(name='boston', version=1, as_frame=True)
boston_df = boston.frame

# Отбираем нужные признаки
X = boston_df['RM'].values.reshape(-1,1)  # средняя стоимость домов
y = boston_df['CRIM'].values  # уровень преступности

# Создание и обучение модели линейной регрессии
model = LinearRegression()
model.fit(X, y)

# Предсказание значений
y_pred = model.predict(X)

# Построение графика линейной регрессии
plt.scatter(X, y, color='blue', label='Наблюдения')
plt.plot(X, y_pred, color='red', linewidth=2, label='Линейная регрессия')
plt.xlabel('Средняя стоимость домов')
plt.ylabel('Уровень преступности')
plt.title('Линейная регрессия: Уровень преступности vs Средняя стоимость домов')
plt.legend()
plt.show()
