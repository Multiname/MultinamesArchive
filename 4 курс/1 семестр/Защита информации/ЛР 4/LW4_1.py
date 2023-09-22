def fast_pow(x, y):
    if y == 0:
        return 1
    if y == -1:
        return 1. / x
    p = fast_pow(x, y // 2)
    p *= p
    if y % 2:
        p *= x
    return p

def encode(message, e, n):
    return fast_pow(message, e) % n

def decode(message, d, n):
    return fast_pow(message, d) % n

n = 221
e = 43
check = [[59, 19], [79, 164], [58, 20]]
for i in range(0, 3):
    if encode(check[i][0], e, n) == check[i][1]:
        print(f'({check[i][0]}, {check[i][1]}): success')
    else:
        print(f'({check[i][0]}, {check[i][1]}): failed')
