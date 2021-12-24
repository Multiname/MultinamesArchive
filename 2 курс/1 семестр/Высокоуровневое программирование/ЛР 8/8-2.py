matrix = [['а', 'е', 'и', 'й', 'к', 'л'],
          ['м', 'р', 'с', 'х', 'ь', 'б'],
          ['в', 'г', 'д', 'ё', 'ж', 'з'],
          ['н', 'о', 'п', 'т', 'у', 'ф'],
          ['ц', 'ч', 'ш', 'щ', 'ъ', 'ы'],
          ['э', 'ю', 'я', ' ', '', '']]
phrase = input('Введите сообщение: ').lower()

cypher = []

for p in range(len(phrase)):
    isFound = False
    for i in range(6):
        for j in range(6):
            if phrase[p] == matrix[i][j]:
                cypher.append([i, j])
                isFound = True
                break
        if isFound:
            break

print('Зашифрованное сообщение:', ' '.join(f'{c[0]}-{c[1]}' for c in cypher))

message = ''

for c in cypher:
    message += matrix[c[0]][c[1]]

print('Дешифрованное сообщение:', message)
