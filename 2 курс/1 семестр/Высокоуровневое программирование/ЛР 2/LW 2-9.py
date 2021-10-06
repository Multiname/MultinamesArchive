import random

N = int(input("N (<= 10): "))
M = int(input("M (<= 10): "))
A = [[random.randint(0, 1) for j in range(M)] for i in range(N)]
print('\n'.join(' '.join(str(i) for i in a) for a in A))

B = []
for a in A:
    isSymmetrical = True
    for i in range(M // 2):
        if a[i] != a[M - i - 1]:
            isSymmetrical = False
            break
    if isSymmetrical:
        B.append(1)
    else:
        B.append(0)

print("B: " + ' '.join(str(b) for b in B))
