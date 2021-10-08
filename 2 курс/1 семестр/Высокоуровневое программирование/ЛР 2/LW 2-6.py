import random
ROST = [random.randint(160, 200) for i in range(70)]
print("ROST: ")
print('\n'.join("{}: {}".format(i, ROST[i]) for i in range(70)))
NR = [i for i in range(70) if ROST[i] < 180]
print("NR: " + ' '.join(str(i) for i in NR))
print("Кол-во: " + str(len(NR)))
