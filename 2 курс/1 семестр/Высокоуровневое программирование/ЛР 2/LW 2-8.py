A = [[j for j in range(1, 21)] for i in range(10)]
print("A:")
print(
    '\n'.join(
        ' '.join("{:>2}".format(A[i][j])
                 for j in range(20))
        for i in range(10)))
