from prettytable import PrettyTable
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt


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

    def print_matrix_base(self):
        names = []
        table = PrettyTable()
        for i in range(self.__SIZE):
            table.add_row(self.__matrix[i])
            names.append("n" + str(i + 1))
        table.field_names = names
        print("Матрица смежности:")
        print(table)
        print()

    def print_matrix_modav(self):
        names = []
        table = PrettyTable()
        matrix = self.__matrix.transpose().copy()
        for i in range(self.__SIZE):
            matrix[i, i] = -1.0
        for i in range(self.__SIZE):
            table.add_row(matrix[i])
            names.append("n" + str(i + 1))
        table.field_names = names
        print("Изменённая матрица для построения СЛАУ:")
        print(table)
        print()

    def __generate_slau_matrix(self):
        matrix_transpose = self.__matrix.transpose()
        for i in range(self.__SIZE):
            matrix_transpose[i, i] = -1.0
        matrix = [[str()] * self.__SIZE for i in range(self.__SIZE)]
        for i in range(self.__SIZE):
            for j in range(self.__SIZE):
                if matrix_transpose[i, j] != self.__NO_WAY:
                    matrix[i][j] = str(matrix_transpose[i, j]) + "*n" + str(j + 1)
                else:
                    matrix[i][j] = ""
        return matrix

    def __generate_slau(self):
        matrix = self.__generate_slau_matrix()
        slau = []
        for i in range(self.__SIZE):
            slau.append("+".join(matrix[i]).replace("++++++++", "+++++++").replace("+++++++", "++++++") \
                        .replace("++++++", "+++++").replace("+++++", "++++").replace("++++", "+++") \
                        .replace("+++", "++").replace("++", "+").replace("+-", "-").replace("1.0", "") \
                        .replace("-*", "-").replace("+*", "+").removeprefix("+").removesuffix("+").removeprefix("*"))
        slau[0] += " = -1"
        for i in range(self.__SIZE - 1):
            slau[i + 1] += " = 0"
        return slau

    def print_slau(self):
        slau = self.__generate_slau()
        print("Система линейных алгебраических уравнений:")
        for i in range(len(slau)):
            print(slau[i])
        print()

    def __solve_slau(self):
        matrix = self.__matrix.transpose()
        for i in range(self.__SIZE):
            matrix[i, i] = -1.0
        vector = [-1.0]
        for i in range(self.__SIZE - 1):
            vector.append(0.0)
        vector = np.array(vector)
        answer = np.linalg.lstsq(matrix, vector, rcond=None)
        return answer[0]

    def print_sovle(self):
        sovle = self.__solve_slau()
        print("Решение СЛАУ:")
        for i in range(len(sovle)):
            print("n" + str(i + 1) + " = " + str(sovle[i]))
        print()

    def __get_laboriousness(self, k1=0.0, k2=0.0, k3=0.0, k4=0.0, k5=0.0, k6=0.0, k7=0.0, k8=0.0):
        sovle = self.__solve_slau()
        k = np.array((k1, k2, k3, k4, k5, k6, k7, k8))
        sum = 0.0
        for i in range(len(k)):
            sum += k[i] * sovle[i]
        return sum

    def print_laboriousness_base(self, k1=0.0, k2=0.0, k3=0.0, k4=0.0, k5=0.0, k6=0.0, k7=0.0, k8=0.0):
        sum = self.__get_laboriousness(k1, k2, k3, k4, k5, k6, k7, k8)
        print("Трудоёмкость по основным операторам составляет: " + str(round(sum)) + " операций")
        print()

    def print_laboriousness_io(self, k1=0.0, k2=0.0, k3=0.0, k4=0.0, k5=0.0, k6=0.0, k7=0.0, k8=0.0):
        sum = self.__get_laboriousness(k1, k2, k3, k4, k5, k6, k7, k8)
        print("Трудоёмкость по операторам ввода/вывода составляет: " + str(round(sum)) + " байт")
        print()

    def print_graph(self):
        G = nx.DiGraph()
        for i in range(self.__SIZE):
            for j in range(self.__SIZE):
                if self.__matrix[i, j] != self.__NO_WAY:
                    G.add_edge(i + 1, j + 1, weight=self.__matrix[i, j])
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
        nx.draw_networkx(G, pos, **options)
        edges = list(G.edges.data("weight"))
        edge_labels = dict()
        for i in range(len(edges)):
            edge_labels.update({(edges[i][0], edges[i][1]): edges[i][2]})
        nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
        plt.axis("off")
        plt.show()


# С седьмой вершиной
if __name__ == '__main__':
    m = Matrix(p12=1.0, p23=0.2, p24=0.3, p25=0.5, p36=1.0, p46=1.0, p56=1.0, p61=0.8, p67=0.2)
    m.print_matrix_base()
    m.print_matrix_modav()
    m.print_graph()
    m.print_slau()
    m.print_sovle()
    m.print_laboriousness_base(k1=100, k2=200, k3=100, k5=300, k6=300) # Основные операторы алгоритма
    m.print_laboriousness_io(k4=200, k7=400) # Операторы ввода-вывода алгоритма


# # Без седьмой вершины
# if __name__ == '__main__':
#     m = Matrix(p12=1.0, p23=0.1, p24=0.3, p25=0.6, p36=1.0, p46=1.0, p56=1.0, p61=0.9)
#     m.print_matrix_base()
#     m.print_matrix_modav()
#     m.print_graph()
#     m.print_slau()
#     m.print_sovle()
#     m.print_laboriousness_base(k1=120, k4=200, k5=300, k6=600) # Основные операторы алгоритма
#     m.print_laboriousness_io(k2=120, k3=150) # Операторы ввода-вывода алгоритма