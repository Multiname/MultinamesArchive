print("Задача 3\n")
number = int(input("Сколько пар вы хотите ввести?: "))
namesAndDates = {}
for i in range(number):
    namesAndDates[input("Введите {}-е имя: ".format(i + 1))] = input("Введите {}-ю дату рождения: ".format(i + 1))
file = open("names and dates.txt", 'w')
file.write('\n'.join("{}: {}".format(pair[0], pair[1]) for pair in namesAndDates.items()))
file.close()
