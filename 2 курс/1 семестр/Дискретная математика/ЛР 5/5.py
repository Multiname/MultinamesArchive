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

Mark = [False]*n
isFound = False
route = []

def DFS(u):
    global isFound
    route.append(u + 1)
    Mark[u] = True
    if u + 1 == target:
        isFound = True
    if not isFound:
        for v in range(n):
            if A[u][v] ==1  and not Mark[v]:
                DFS(v)
                if isFound:
                    return
                else:
                    route.pop()
    
DFS(source-1)
print('Путь из {} в {} в глубину: '.format(source, target), end = '')
if isFound:
    print(' -> '.join(str(i) for i in route))
    print('Длина =', len(route) - 1)
else:
    print('не найден')

Mark = [False]*n
Q = [source - 1]
Mark[source - 1] = True
head = 0
elementsInTier = [1, 0]
tiers = [[source], []]
currentTier = 0

while head < len(Q):
    u = Q[head]
    elementsInTier[currentTier] -= 1
    for v in range(n):
        if A[u][v] == 1 and not Mark[v]:
            Mark[v] = True
            elementsInTier[currentTier + 1] += 1
            tiers[currentTier + 1].append(v + 1)
            Q.append(v)
    head += 1
    if elementsInTier[currentTier] == 0:
        currentTier += 1
        elementsInTier.append(0)
        tiers.append([])
tiers.pop()
tiers.pop()

i = 0
while i < len(tiers) and not target in tiers[i]:
    i += 1

print('Путь из {} в {} в ширину: '.format(source, target), end = '')
if i < len(tiers):
    route = [0] * (i + 1)
    route[i] = target
    while i > 0:
        for t in tiers[i - 1]:
            if A[t - 1][route[i] - 1]:
                route[i - 1] = t
                break
        i -= 1

    print(' -> '.join(str(i) for i in route))
    print('Длина =', len(route) - 1)
else:
    print('не найден')
