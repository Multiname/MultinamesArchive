import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.cluster import KMeans
from scipy.cluster.hierarchy import dendrogram, linkage

# Считываем данные из файла iris_df.csv в DataFrame
iris_df = pd.read_csv('iris_df.csv')

# Построение графика для выбора числа кластеров
sns.set(style='whitegrid')
sns.pairplot(iris_df, hue='Species', markers=["o", "s", "D"])
plt.show()

# Выбираем данные для кластеризации
X = iris_df[['Petal Length', 'Petal Width']]

# K-means кластеризация
kmeans = KMeans(n_clusters=3)
kmeans.fit(X)
centroids = kmeans.cluster_centers_

# Построение графика кластеризации
plt.figure(figsize=(8, 6))
plt.scatter(X['Petal Length'], X['Petal Width'], c=kmeans.labels_, cmap='viridis', s=50, alpha=0.5)
plt.scatter(centroids[:, 0], centroids[:, 1], c='red', marker='X', s=200)
plt.xlabel('Petal Length')
plt.ylabel('Petal Width')
plt.title('K-means Clustering')
plt.show()

# Иерархическая кластеризация
Z = linkage(X, method='single')

# Построение дендрограммы
plt.figure(figsize=(10, 7))
dendrogram(Z, labels=iris_df['Species'].values)
plt.title('Hierarchical Clustering Dendrogram')
plt.xlabel('Species')
plt.ylabel('Distance')
plt.show()
