import numpy
from scipy import linalg
import matplotlib.pyplot as plt

array = numpy.random.sample((5, 5))
print('Случайная матрица')
print(array)
array = array * 10
print('Умножение на 10')
print(array)
array = array.astype(numpy.int32)
print('Приведение к int')
print(array)
det_1 = linalg.det(array)
print('Первый определитель:', det_1)
array = linalg.inv(array)
print('Обратная матрица')
print(array)
det_2 = linalg.det(array)
print('Второй определитель:', det_2)

x = [1, 2]
y = [det_1, det_2]
plt.bar(x, y)
plt.grid(True)
plt.show()
