import random
import math
from datetime import datetime

N = int(input("Введите размер массива: "))

print("\nВыберете способ ввода массива")
print("1. В ручную")
print("2. Случайно")
print("3. Возрастающими числами")
print("4. Убывающими числами")
means = input(">>> ")
print()

A = []
if means == '1':
    A = [int(input("{}: ".format(i + 1))) for i in range(N)]
elif means == '2':
    minimum = int(input("Введите минимальное число: "))
    maximum = int(input("Введите максимальное число: "))
    A = [random.randint(minimum, maximum) for i in range(N)]
elif means == '3':
    A = [i + 1 for i in range(N)]
elif means == '4':
    A = [i for i in range(N, 0, -1)]
else:
    print("Ошибка ввода")

print("\nСозданный массив: " + ' '.join(str(a) for a in A))

print("\nВыберите способ сортировки")
print("1. Выбором")
print("2. Обменом")
print("3. Вставками")
print("4. Слиянием")
print("5. QuickSort")
means = input(">>> ")
print()

start = datetime
end = datetime
if means == '1':
    start = datetime.now()
    for i in range(N - 1):
        minimum = A[i]
        index = i
        for j in range(i + 1, N):
            if A[j] < minimum:
                minimum = A[j]
                index = j
        if i != index:
            A[i], A[index] = A[index], A[i]
    end = datetime.now()
elif means == '2':
    start = datetime.now()
    for i in range(N - 1):
        for j in range(N - i - 1):
            if A[j] > A[j + 1]:
                A[j], A[j + 1] = A[j + 1], A[j]
    end = datetime.now()
elif means == '3':
    start = datetime.now()
    for i in range(1, N):
        for j in range(i):
            if A[i] < A[j]:
                for k in range(i, j, -1):
                    A[k], A[k - 1] = A[k -1], A[k]
    end = datetime.now()
elif means == '4':
    def MergeSort(A):
        if len(A) > 2:
            L = A[:len(A)//2]
            R = A[len(A)//2:]
            MergeSort(L)
            MergeSort(R)
            l = r = a = 0
            while l < len(L) and r < len(R):
                if L[l] < R[r]:
                   A[a] = L[l]
                   l += 1
                else:
                    A[a] = R[r]
                    r += 1
                a += 1
            if l < len(L):
                for i in range(l, len(L)):
                    A[a] = L[i]
                    a += 1
            else:
                for i in range(r, len(R)):
                    A[a] = R[i]
                    a += 1
        elif len(A) == 2:
            if A[0] > A[1]:
                A[0], A[1] = A[1], A[0]

    start = datetime.now()
    MergeSort(A)
    end = datetime.now()
elif means == '5':
    def QuickSort(A):
        if len(A) > 1:
            pivot = A[0]
            L = []
            R = []
            for a in A[1:]:
                if a < pivot:
                    L.append(a)
                else:
                    R.append(a)
            L = QuickSort(L)
            R = QuickSort(R)
            L.append(pivot)
            A = L + R
        return A

    start = datetime.now()
    A = QuickSort(A)
    end = datetime.now()
else:
    print("Ошибка ввода")

print("Отсортированный массив: " + ' '.join(str(a) for a in A))

minimum = math.inf
for i in range(len(A) - 1):
    if A[i + 1] - A[i] < minimum:
        minimum = A[i + 1] - A[i]
print("Контрольное значение: {}".format(minimum))
print("Время работы: {}".format(end - start))
