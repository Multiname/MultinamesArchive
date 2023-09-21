import random, math

max_prime = int(input('Введите максимально возможное значение p и q: '))
 
primes = [i for i in range(max_prime + 1)]
primes[1] = 0
i = 2
while i <= max_prime:
    if primes[i] != 0:
        j = i + i
        while j <= max_prime:
            primes[j] = 0
            j = j + i
    i += 1
 
primes = [i for i in primes if i != 0]
primes.remove(2)

p = primes[random.randint(0, len(primes) - 1)]
primes.remove(p)
q = primes[random.randint(0, len(primes) - 1)]
if p*q < 33:
    primes.remove(q)
    q = primes[random.randint(0, len(primes) - 1)]
print('p =', p)
print('q =', q)

n = p*q
print('n =', n)
phi = (p - 1)*(q - 1)
print('phi =', phi)

e = random.randint(2, phi - 1)
while math.gcd(e, phi) != 1:
    e = random.randint(2, phi - 1)
print('e =', e)

k = 1
while (k * phi + 1) % e != 0:
    k += 1
d = (k * phi + 1) // e

print('d =', d)

source = 'интерполятор'

encrypted = []
for s in source:
    s = ord(s) - 1072
    encrypted.append(s**e % n)
print('Шифр:', encrypted)

decrypted = ''
for s in encrypted:
    decrypted += chr(s**d % n + 1072)
print('Исходный текст:', decrypted)
print()

q = 71
a = 7
X_A = 5
Y_B = 11
K = 23

Y_A = a**X_A % q
print('Y_A =', Y_A)

K_A = Y_B**X_A % q
print('K_A =', K_A)