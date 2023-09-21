key = input("input key: ")

d = len(key)
n = 26
i = 0

file = open('input.txt', 'r')
text = file.read()

mode = int(input('input mode (0 - encrypt, 1 - decrypt): '))
if mode == 0:
    cypher = ""
    for l in text:
        if l.isalpha():
            m = ord(l.lower()) - 97
            k = int(key[i % d])
            cypher += chr((m + k) % n + 97)
        else:
            cypher += l
    print('cypher:', cypher)
elif mode == 1:
    source = ""
    for l in text:
        if l.isalpha():
            m = ord(l.lower()) - 97
            k = int(key[i % d])
            source += chr((m - k) % n + 97)
        else:
            source += l
    print('source:', source)
else:
    print('error')
