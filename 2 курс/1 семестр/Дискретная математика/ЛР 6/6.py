import math

n = int
source = int
target = int
A = []

with open('data.txt') as f:
    n, source, target = f.readline().split()
    n = int(n)
    source = int(source)
    target = int(target)

    print('  ', ''.join('{:>3}'.format(i + 1) for i in range(n)))
    print()
    for line in f:
        numbers = line.split()
        A.append([int(numbers[i]) for i in range(n)])
        print('{:>2}'.format(len(A)), ''.join('{:>3}'.format(i) for i in numbers))
print()

for i in range(n):
    for j in range(n):
        if i == j:
            A[i][j] = 0
        elif A[i][j] == 0:
            A[i][j] = math.inf

d = A[source-1].copy()
for k in range(n-2):
    for v in range(n):
        for u in range(n):
            d[v] = min(d[v],d[u]+A[u][v])

print('Алгоритм Форда-Беллмана:')
print(d)

Mark = [False]*n
d = [math.inf]*n
d[source-1] = 0
prev = [None]*n

for i in range(n-1):
    m = math.inf
    for v in range(n):
        if (not Mark[v]) and (d[v]<m):
            m = d[v]
            u = v
        Mark[u] = True
        for v in range(n):
            if (not Mark[v]) and (d[u]+A[u][v]<d[v]):
                d[v] = d[u] + A[u][v]
                prev[v] = u

Path = [target-1]
v = target-1
while v!=source-1:
    v = prev[v]
    Path.insert(0,v)
    
print('Алгоритм Дейкстры:')
print('Путь: ', ' -> '.join(str(i + 1) for i in Path))
print('Расстояние =', d[target-1])

for k in range(n):
    for u in range(n):
        for v in range(n):
            A[u][v] = min(A[u][v], A[u][k]+A[k][v])

print('Алгоритм Флойда-Уоршалла:')
print('  ', ''.join('{:>4}'.format(i + 1) for i in range(n)))
print()
for i in range(n):
    print('{:>2}'.format(i + 1), ''.join('{:>4}'.format(a) for a in A[i]))
