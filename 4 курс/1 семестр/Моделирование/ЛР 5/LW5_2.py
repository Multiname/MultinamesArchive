from prettytable import PrettyTable
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np


class Matrix:
    __NO_WAY = 0.0
    __SIZE = 8

    def __init__(self,
                 p12=__NO_WAY, p13=__NO_WAY, p14=__NO_WAY,
                 p23=__NO_WAY, p24=__NO_WAY, p25=__NO_WAY,
                 p34=__NO_WAY, p35=__NO_WAY, p36=__NO_WAY, p37=__NO_WAY,
                 p45=__NO_WAY, p46=__NO_WAY, p47=__NO_WAY,
                 p56=__NO_WAY, p57=__NO_WAY,
                 p61=__NO_WAY, p67=__NO_WAY, p68=__NO_WAY,
                 p71=__NO_WAY, p72=__NO_WAY, p78=__NO_WAY,
                 p81=__NO_WAY):
        self.__matrix = np.zeros((self.__SIZE, self.__SIZE))
        self.__matrix[0, 1] = p12
        self.__matrix[0, 2] = p13
        self.__matrix[0, 3] = p14
        self.__matrix[1, 2] = p23
        self.__matrix[1, 3] = p24
        self.__matrix[1, 4] = p25
        self.__matrix[2, 3] = p34
        self.__matrix[2, 4] = p35
        self.__matrix[2, 5] = p36
        self.__matrix[2, 6] = p37
        self.__matrix[3, 4] = p45
        self.__matrix[3, 5] = p46
        self.__matrix[3, 6] = p47
        self.__matrix[4, 5] = p56
        self.__matrix[4, 6] = p57
        self.__matrix[5, 0] = p61
        self.__matrix[5, 6] = p67
        self.__matrix[5, 7] = p68
        self.__matrix[6, 0] = p71
        self.__matrix[6, 1] = p72
        self.__matrix[6, 7] = p78
        self.__matrix[7, 0] = p81
        self.__G = nx.DiGraph()
        self.__removed_edge_weight = 0.0
        self.__map = {}
        for i in range(self.__SIZE):
            for j in range(self.__SIZE):
                if self.__matrix[i, j] != self.__NO_WAY:
                    self.__G.add_edge(i + 1, j + 1, weight=self.__matrix[i, j])

    def print_matrix(self):
        names = []
        table = PrettyTable()
        for i in range(self.__SIZE):
            table.add_row(self.__matrix[i])
            names.append("n" + str(i + 1))
        table.field_names = names
        print("Матрица смежности:")
        print(table)
        print()

    def print_graph(self):
        options = {
            "font_size": 14,
            "node_size": 1000,
            "node_color": "white",
            "edgecolors": "black",
            "linewidths": 3,
            "width": 3,
        }
        pos = {1: (0.0, 1.0), 2: (0.7, 0.7), 3: (1.0, 0.0), 4: (0.7, -0.7),
               5: (0.0, -1.0), 6: (-0.7, -0.7), 7: (-1.0, 0.0), 8: (-0.7, 0.7)}
        nx.draw_networkx(self.__G, pos, **options)
        edges = list(self.__G.edges.data("weight"))
        edge_labels = dict()
        for i in range(len(edges)):
            edge_labels.update({(edges[i][0], edges[i][1]): edges[i][2]})
        nx.draw_networkx_edge_labels(self.__G, pos, edge_labels=edge_labels)
        plt.axis("off")
        plt.show()

    def refactory_graph(self, map):
        self.__map = map
        self.__G = nx.relabel_nodes(self.__G, self.__map)
        for edge in nx.edges(self.__G).data("weight"):
            G = self.__G.copy()
            G.remove_edge(edge[0], edge[1])
            if len(list(nx.simple_cycles(G))) == 0:
                self.__G = G
                self.__removed_edge_weight = edge[2]
                break
        edges = list(self.__G.edges.data("weight"))
        for i in range(self.__SIZE):
            for j in range(self.__SIZE):
                self.__matrix[i, j] = 0.0
        for edge in edges:
            self.__matrix[edge[0] - 1, edge[1] - 1] = edge[2]

    def __find_n(self):
        n = np.zeros(self.__SIZE)
        n[0] = 1.0
        for i in range(1, self.__SIZE):
            sum = 0.0
            for j in range(self.__SIZE):
                sum += self.__matrix[j, i] * n[j]
            n[i] = sum
        return n

    def __get_laboriousness(self, k1=0.0, k2=0.0, k3=0.0, k4=0.0, k5=0.0, k6=0.0, k7=0.0, k8=0.0):
        k_base = np.array((k1, k2, k3, k4, k5, k6, k7, k8))
        k_mapped = k_base.copy()
        for key in self.__map:
            k_mapped[self.__map[key] - 1] = k_base[key - 1]
        k_mapped = np.array(k_mapped)
        sum = 0.0
        n = self.__find_n()
        p = 1.0
        for i in range(self.__SIZE - 1, 0, -1):
            if n[i] != 0.0:
                p = n[i]
                n[i] = 1.0
                break
        for i in range(len(k_mapped)):
            sum += k_mapped[i] * n[i]
        sum /= (1.0 - (p * self.__removed_edge_weight))
        return sum

    def print_laboriousness_base(self, k1=0.0, k2=0.0, k3=0.0, k4=0.0, k5=0.0, k6=0.0, k7=0.0, k8=0.0):
        sum = self.__get_laboriousness(k1, k2, k3, k4, k5, k6, k7, k8)
        print("Трудоёмкость по основным операторам составляет: " + str(round(sum)) + " операций")
        print()

    def print_laboriousness_io(self, k1=0.0, k2=0.0, k3=0.0, k4=0.0, k5=0.0, k6=0.0, k7=0.0, k8=0.0):
        sum = self.__get_laboriousness(k1, k2, k3, k4, k5, k6, k7, k8)
        print("Трудоёмкость по операторам ввода/вывода составляет: " + str(round(sum)) + " байт")
        print()


# С седьмой вершиной
if __name__ == '__main__':
    m = Matrix(p12=1.0, p23=0.2, p24=0.3, p25=0.5, p36=1.0, p46=1.0, p56=1.0, p61=0.8, p67=0.2)
    m.print_graph()
    m.print_matrix()
    map = {2: 1, 5: 2, 6: 5, 7: 6, 1: 7}
    m.refactory_graph(map)
    m.print_graph()
    m.print_matrix()
    m.print_laboriousness_base(k1=100, k2=200, k3=100, k5=300, k6=300) # Основные операторы алгоритма
    m.print_laboriousness_io(k4=200, k7=400) # Операторы ввода-вывода алгоритма

# # Без седьмой вершины
# if __name__ == '__main__':
#     m = Matrix(p12=1.0, p23=0.1, p24=0.3, p25=0.6, p36=1.0, p46=1.0, p56=1.0, p61=0.9)
#     m.print_graph()
#     m.print_matrix()
#     map = {2: 1, 5: 2, 6: 5, 1: 6}
#     m.refactory_graph(map)
#     m.print_graph()
#     m.print_matrix()
#     m.print_laboriousness_base(k1=120, k4=200, k5=300, k6=600) # Основные операторы алгоритма
#     m.print_laboriousness_io(k2=120, k3=150) # Операторы ввода-вывода алгоритма