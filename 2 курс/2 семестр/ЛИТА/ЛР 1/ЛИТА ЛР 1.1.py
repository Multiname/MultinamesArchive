import random
import math
from datetime import datetime
import csv

def Algorithm(array, N, M):                 # N * 2^N
    code = 0                                # c1
    average = -math.inf                     # c2
    biggestCode = None                      # c3
    while code + 1 != 2**N:                 # 2^N * c4
        code += 1                           # (2^N  - 1) * c5
        size = 0                            # (2^N  - 1) * c6
        position = 0                        # (2^N  - 1) * c7
        summ = 0                            # (2^N  - 1) * c8
        for b in bin(code)[2:][::-1]:       # (2^N  - 1) * c9
            position += 1                   # (2^N * (N-1) + 1)  * c10
            if b == '1':                    # (2^N * (N-1) + 1)  * c11
                size += 1                   # 2^(N-1) * N * c12
                summ += array[-position]    # 2^(N-1) * N * c13
        if size == M:                       # (2^N  - 1) * c14
            if summ / M > average:          # N! / (M!(N-M)!) * c15
                average = summ / M          # c16 || N! / (M!(N-M)!) * c16
                biggestCode = code          # c17 || N! / (M!(N-M)!) * c17
    return biggestCode

N_min = 10
N_max = 25
N_delta = 1

with open('data.csv', 'w', encoding='utf-8', newline='') as f:
    writer = csv.writer(f)
    for N in range(N_min, N_max + 1, N_delta):
        M = N // 2
        array = [random.randint(-10, 10) for i in range(N)]
        
        start = datetime.now()
        biggestCode = Algorithm(array, N, M)
        end = datetime.now()
        
        result = []
        for i in range(len(bin(biggestCode)) - 2):
            if bin(biggestCode)[-i - 1] == '1':
                result.append(array[-i - 1])
        print(N, end - start, array, result[::-1])
        writer.writerow([N, end - start])
