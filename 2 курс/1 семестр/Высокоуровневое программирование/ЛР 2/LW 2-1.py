size = int(input("Введите размер матриц: "))
L = [[0 for i in range(size)] for j in range(size)]
K = [[0 for i in range(size)] for j in range(size)]
M = [[False for i in range(size)] for j in range(size)]
print("\nL:")
for i in range(size):
    for j in range(size):
        if i == j:
            L[i][j] = 2
        if i >= j:
            K[i][j] = 7
        M[i][j] = not(L[i][j] + K[i][j])
        print(str(L[i][j]) + " ", end = '')
    print()
print("\nK:")
print("\n".join(" ".join(str(i) for i in k) for k in K))
print("\nM:")
print("\n".join(" ".join(str(int(i)) for i in m) for m in M))
