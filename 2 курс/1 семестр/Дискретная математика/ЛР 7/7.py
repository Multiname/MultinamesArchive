import math

n = int
A = []

with open('data.txt') as f:
    n = f.readline()
    n = int(n)

    print('  ', ''.join('{:>3}'.format(i + 1) for i in range(n)))
    print()
    for line in f:
        numbers = line.split()
        A.append([int(numbers[i]) for i in range(n)])
        print('{:>2}'.format(len(A)), ''.join('{:>3}'.format(i) for i in numbers))
print()

weight = 0
frame = []
marks = [i for i in range(n)]
edges = []
for i in range(n):
    for j in range(i + 1, n):
        edges.append([A[i][j], i, j])
edges.sort()

edgesInFrame = 0
for edge in edges:
    if marks[edge[1]] != marks[edge[2]]:
        weight += edge[0]
        frame.append([edge[1] + 1, edge[2] + 1])
        edgesInFrame += 1
        markToChange = marks[edge[2]]
        for i in range(n):
            if marks[i] == markToChange:
                marks[i] = marks[edge[1]]
        if edgesInFrame == n - 1:
            break

print('Алгоритм Краскала:', ' '.join(f'{i[0]}-{i[1]}' for i in frame))
print('Вес =', weight)

weight = 0
frame = []
marks = [i for i in range(n)]
edgesInFrame = 0
for i in range(n - 1):
    minEdge = [math.inf]
    side = int
    for edge in edges:
        if edge[0] < minEdge[0]:
            if marks[edge[1]] == 0 and marks[edge[2]] != 0:
                minEdge = edge
                side = 2
            elif marks[edge[2]] == 0 and marks[edge[1]] != 0:
                minEdge = edge
                side = 1
    weight += minEdge[0]
    frame.append([minEdge[1] + 1, minEdge[2] + 1])
    markToChange = marks[minEdge[side]]
    for j in range(n):
        if marks[j] == markToChange:
            marks[j] = 0

print('Алгоритм Прима:', ' '.join(f'{i[0]}-{i[1]}' for i in frame))
print('Вес =', weight)
