import sys

string = input("Введите строку: ").upper()
for s in string:
    if not s.isdigit() and (s < 'A' or 'F' < s):
        print("Это не шестнадцатеричное число")
        sys.exit()
print("Это шестнадцатеричное число")
