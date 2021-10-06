import math

print ("Задача №1")

a, b = input("Введите целые числа a и b: ").split()
a = int(a)
b = int(b)
c = float(input("Введите действительное число c: "))

X = round(pow(math.e, a / (b + c)) + math.sqrt(a**2 + b**2) - 1 / (c**3 + a * b), 2)
Y = round(math.sin(a) + math.sqrt(math.cos(b**b)) - math.tan(a / b), 2)
print("X = ", X)
print("Y = ", Y)


print("\nЗадача №2")

x, y = input("Введите координаты точки (x, y): ").split()
x = float(x)
y = float(y)
print(x >= -10 and x <= 10 and y <= x + 10 and y <= 10 - x and y >= 0)


print("\nЗадача №3")
a = float(input("Введите действительное число a: "))
r = int(math.sqrt(abs(a**2 + math.sin(a))) + a**2)
print("Третья цифра с конца целой части: ", end = '')
if r < 100:
    print(0)
else:
    print(str(r)[-3])
