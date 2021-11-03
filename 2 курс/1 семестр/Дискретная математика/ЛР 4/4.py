file = open("data.txt", 'r')
N = int(file.readline())
A = []
print("Матрица стоимостей:")
for line in file:
    numbers = line.split()
    A.append([int(numbers[i]) for i in range(N)])
    print(' '.join("{:>3}".format(numbers[i]) for i in range(N)))
file.close()
    
x = [i for i in range(1, N + 1)]

def next():
    global x, N
    i = N - 2
    while i >= 0 and x[i] > x[i + 1]:
        i -= 1
    if i >= 0:
        j = i + 1
        while j < N - 1 and x[j + 1] > x[i]:
            j += 1
        x[i], x[j] = x[j], x[i]
        for j in range(i + 1, (i + N)//2 + 1):
            x[j], x[N - j + i] = x[N - j + i], x[j]
        return True
    else:
        return False

cheapest = x.copy()
minimum = sum([A[i][i + 1] for i in range(N - 1)]) + A[N - 1][0]
control = 1
while next():
    if (x[0] != 1):
        break
    control += 1
    cost = A[x[N - 1] - 1][x[0] - 1]
    for i in range(N - 1):
        cost += A[x[i] - 1][x[i + 1] - 1]
    if cost < minimum:
        minimum = cost
        cheapest = x.copy()

print("\nОптимальный маршрут:")
print(" -> ".join(str(cheapest[i]) for i in range(N)) + " -> 1")
print("Стоимость: {}".format(minimum))
print("Контрольное значение: {}".format(control))
