import matplotlib.pyplot as plt
import math

ax = plt.subplot()

x = [i/100 for i in range(-314, 315)]
y = [math.sin(i) for i in x]
ax.plot(x, y, color = 'white')

ax.set_xlabel('Время')
ax.set_ylabel('Амплитуда')

ax.spines['bottom'].set_color('blue')
ax.spines['top'].set_color('blue')
ax.spines['left'].set_color('blue')
ax.spines['right'].set_color('blue')
ax.grid(c = 'blue')
ax.set_facecolor('orange')

plt.show()
