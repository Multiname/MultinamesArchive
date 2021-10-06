for number in range(1000, 10000):
    if (number % 2 == 0 and number % 7 == 0 and number % 11 == 0
    and number // 1000 + number // 100 % 10 + number // 10 % 10 + number % 10 == 30
    and len({number // 1000, number // 100 % 10, number // 10 % 10, number % 10}) == 2):
        print(number)
