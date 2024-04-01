import networkx as nx
import matplotlib.pyplot as plt
import csv

# Загрузка данных о связях друзей (предполагается, что данные находятся в файле friends.csv)
def load_friend_data(file_path):
    friend_data = {}
    with open(file_path, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            node = row[0]
            friends = row[1:]
            friend_data[node] = friends
    return friend_data

# Сохранение значений центральностей в файл
def save_centralities_to_file(centralities, file_path):
    with open(file_path, 'w') as file:
        for node, centrality_values in centralities.items():
            file.write(f"{node} - {centrality_values['betweenness']} - {centrality_values['closeness']} - {centrality_values['eigenvector']}\n")

# Загрузка данных о связях друзей
friend_data = load_friend_data('friends.csv')

# Создание графа
G = nx.Graph()
for node, friends in friend_data.items():
    for friend in friends:
        G.add_edge(node, friend)

# Визуализация графа
plt.figure(figsize=(10, 8))
nx.draw(G, with_labels=True)
plt.savefig("friend_network_graph.png")
plt.close()

# Вычисление мер центральности
betweenness = nx.betweenness_centrality(G)
closeness = nx.closeness_centrality(G)
eigenvector = nx.eigenvector_centrality(G)

# Сохранение значений центральностей в файл
centralities = {}
for node in G.nodes():
    centralities[node] = {
        'betweenness': betweenness[node],
        'closeness': closeness[node],
        'eigenvector': eigenvector[node]
    }
save_centralities_to_file(centralities, 'centralities.txt')

# Построение графика распределения степени узлов
degrees = [G.degree(node) for node in G.nodes()]
plt.hist(degrees, bins=20)
plt.xlabel('Degree')
plt.ylabel('Frequency')
plt.savefig('degree_distribution.png')
plt.close()
