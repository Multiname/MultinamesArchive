import os

while True:
    command = int(input("Выберите задачу (1-4), для выхода введите 0: "))
    os.system("cls")

    if command == 0:
        break
    
    if command == 1:
        print("Предложение с заглавными буквами: " + ' '.join(word.capitalize() for word in input("Введите предложение на английском: ").split(" ")))

    elif command == 2:
        N = int(input("Кол-во элементов N: "))
        numbers = []
        minimum = float("inf")
        print("Введите вещественные числа")
        for i in range(N):
            numbers.append(float(input(str(i + 1) + ": ")))
            if abs(numbers[i]) < minimum:
                minimum = numbers[i]
                
        print("Минимальный по модулю элемент: " + str(minimum))
        numbers.reverse()
        print("Массив в обратном порядке: " + " ".join(str(number) for number in numbers))

    elif command == 3:
        A = ["A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9"]
        B = ["B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9"]
        print("Матрицы до изменения")
        print("A: " + " ".join(a for a in A))
        print("B: " + " ".join(b for b in B))
        
        for i in range(10):
            A[i], B[i] = B[i], A[i]
        print("Матрицы после изменения")
        print("A: " + " ".join(a for a in A))
        print("B: " + " ".join(b for b in B))

    elif command == 4:
        peopleTuple = ("Ivan", 18, "Petr", 19, "Oleg", 20, "Kate", 21)
        print("Кортеж: " + str(peopleTuple))
        
        peopleDictionary = {}
        for i in range(0, len(peopleTuple), 2):
            peopleDictionary[peopleTuple[i + 1]] = peopleTuple[i]
        print("Словарь: " + str(peopleDictionary))
        
    input()
    os.system("cls")
