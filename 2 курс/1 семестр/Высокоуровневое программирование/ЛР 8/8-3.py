key = 'аеийклмрсхь'
phrase = input('Введите сообщение: ').lower()
cypher = ''

while len(key) < len(phrase):
    key += key

for i in range(len(phrase)):
    if phrase[i].isalpha():
        cypher += chr((ord(phrase[i]) + ord(key[i]) - 2144) % 33 + 1072)
    else:
        cypher += phrase[i]

print('Зашифрованное сообщение:', cypher)

message = ''

for i in range(len(cypher)):
    if cypher[i].isalpha():
        message += chr((ord(cypher[i]) - ord(key[i])) % 33 + 1072)
    else:
        message += cypher[i]
        
print('Дешифрованное сообщение:', message)
