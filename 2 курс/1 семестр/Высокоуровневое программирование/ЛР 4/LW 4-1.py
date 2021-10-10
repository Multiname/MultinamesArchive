print("Задача 1\n")
file = open("Students.txt", 'r', encoding = 'utf-8')
for line in file:
    words = line.split()
    numberOfDebts = 0
    for i in range(0, 3):
        if int(words[i + 1]) < 3:
            numberOfDebts += 1
    if numberOfDebts > 0:
        print(words[0] + ": " + str(numberOfDebts))
file.close()
