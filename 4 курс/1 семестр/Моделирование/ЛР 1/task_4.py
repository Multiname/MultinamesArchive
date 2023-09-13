import numpy as np
from matplotlib import cm
import matplotlib.pyplot as plt
import math

eps = 10**-6

f = lambda x, y: x**2 + 0.5*x*y + 2.5*y**2 - 2*x - 10.5*y

df_x = lambda x, y: 2*x + 0.5*y - 2
df_y = lambda x, y: 0.5*x + 5*y - 10.5

d2f_x = 2
d2f_y = 5
det = d2f_x * d2f_y

x = [0]
y = [3]

p = [(df_x(x[0], y[0]), df_y(x[0], y[0]))]

lmd = (df_x(x[0], y[0]) * p[0][0] + df_y(x[0], y[0]) * p[0][1]) / ((p[0][0]**2 + p[0][1]**2) * det)

x.append(x[0] - lmd * p[0][0])
y.append(y[0] - lmd * p[0][1])

n = 0
while math.sqrt(p[-1][0]**2 + p[-1][1]**2) > eps:
    frac = (df_x(x[-1], y[-1])**2 + df_y(x[-1], y[-1])**2) / (df_x(x[-2], y[-2])**2 + df_y(x[-2], y[-2])**2)
    p_1 = df_x(x[-1], y[-1]) + p[-1][0] * frac
    p_2 = df_y(x[-1], y[-1]) + p[-1][1] * frac
    p.append((p_1, p_2))

    lmd = (df_x(x[-1], y[-1]) * p_1 + df_y(x[-1], y[-1]) * p_2) / ((p_1**2 + p_2**2) * det)

    x.append(x[-1] - lmd * p_1)
    y.append(y[-1] - lmd * p_2)

    n += 1

print(f"x = {x[-1]:.6f}")
print(f"y = {y[-1]:.6f}")
print(f"f(x, y) = {f(x[-1], y[-1]):.6f}")
print(f"n = {n}")


x = [0]
y = [3]

det_inv = 1 / 9.75
H_inv = [[det_inv * 5, det_inv * -0.5], 
         [det_inv * -0.5, det_inv * 2]]

n = 0
while math.sqrt(df_x(x[-1], y[-1])**2 + df_y(x[-1], y[-1])**2) > eps:
    x_k = x[-1] - (H_inv[0][0] * df_x(x[-1], y[-1]) + H_inv[0][1] * df_y(x[-1], y[-1]))
    y_k = y[-1] - (H_inv[1][0] * df_x(x[-1], y[-1]) + H_inv[1][1] * df_y(x[-1], y[-1]))

    x.append(x_k)
    y.append(y_k)

    n += 1

print(f"x = {x[-1]:.6f}")
print(f"y = {y[-1]:.6f}")
print(f"f(x, y) = {f(x[-1], y[-1]):.6f}")
print(f"n = {n}")

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

X = np.arange(-10, 10, 0.25)
Y = np.arange(-10, 10, 0.25)
X, Y = np.meshgrid(X, Y)
Z = X**2 + 0.5*X*Y + 2.5*Y**2 - 2*X - 10.5*Y

surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
                       linewidth=0, antialiased=False)
plt.show()