print("Задача 2\n")
file = open("f.txt", 'r', encoding = 'utf-8')
text = '\n'.join(''.join(line.split()) + ' '*(len(line.split()) - 1) for line in file)
file.close()
file = open("f.txt", 'w', encoding = 'utf-8')
file.write(text)
file.close()
