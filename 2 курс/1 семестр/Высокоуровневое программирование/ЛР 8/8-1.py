key = 10
phrase = input('Введите сообщение: ').lower()
cypher = ''

for i in range(len(phrase)):
    if phrase[i].isalpha():
        if ord(phrase[i]) + key > 122:
            cypher += chr(ord(phrase[i]) + key - 26)
        else:
            cypher += chr(ord(phrase[i]) + key)
    else:
        cypher += phrase[i]

print('Зашифрованное сообщение:', cypher)

message = ''

for i in range(len(cypher)):
    if phrase[i].isalpha():
        if ord(cypher[i]) - key < 97:
            message += chr(ord(cypher[i]) - key + 26)
        else:
            message += chr(ord(cypher[i]) - key)
    else:
        message += cypher[i]

print('Дешифрованное сообщение:', message)
