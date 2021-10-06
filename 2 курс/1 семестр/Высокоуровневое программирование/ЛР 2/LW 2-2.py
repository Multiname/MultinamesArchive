print(' '.join(str(num) for num in range(100, 1000)
               if num == (num // 100)**3 +
               ((num // 10) % 10)**3 + (num % 10)**3))
