import matplotlib.pyplot as plt

x1 = [i/10 for i in range(-100, 0)]
y1 = [(2 * i  + 1) / i  for i in x1]
x2 = [i/10 for i in range(1, 101)]
y2 = [(2 * i  + 1) / i  for i in x2]
ax = [0, 0]
ay = [-13, 13]
plt.plot(x1, y1, x2, y2, ax, ay, '--')
plt.show()
