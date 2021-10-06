k = int(input("k: "))
cubes = "1"
number = 2
while len(cubes) < k:
    cubes += str(number**3)
    number += 1
print(cubes + "...")
print("{}-я цифра: ".format(k) + cubes[k - 1])
