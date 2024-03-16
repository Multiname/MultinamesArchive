import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeRegressor, plot_tree
from sklearn.preprocessing import LabelEncoder
import matplotlib.pyplot as plt

# Загрузка данных из файла iris_df.csv в DataFrame
iris_df = pd.read_csv('iris_df.csv')

# Преобразование категориальной переменной в числовую
label_encoder = LabelEncoder()
iris_df['Species'] = label_encoder.fit_transform(iris_df['Species'])

# Выбираем поле "Sepal width" в качестве целевой переменной
X = iris_df.drop(columns=['Sepal width'])
y = iris_df['Sepal width']

# Разделение данных на обучающий и тестовый наборы
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Построение двух деревьев решений с различными глубинами
depths = [2, 3]  # выбранные глубины деревьев
models = []

for depth in depths:
    # Создание модели дерева решений
    model = DecisionTreeRegressor(max_depth=depth)
    # Обучение модели
    model.fit(X_train, y_train)
    models.append(model)

# Визуализация двух деревьев решений на разных графиках
for i, model in enumerate(models, 1):
    plt.figure(figsize=(12, 6))
    plot_tree(model, filled=True, feature_names=X.columns)
    plt.title(f'Decision Tree with Max Depth = {depths[i-1]}')
    plt.show()
