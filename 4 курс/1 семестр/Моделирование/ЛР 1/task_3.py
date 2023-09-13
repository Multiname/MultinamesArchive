import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
from scipy import optimize

x_1 = -2
x_2 = 2
y_1 = -2
y_2 = 2
eps = 10**-6

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

X = np.arange(x_1, x_2, 0.25)
Y = np.arange(y_1, y_2, 0.25)
X, Y = np.meshgrid(X, Y)
Z = 3*X**2 + Y**2 + np.log(X**2 + Y**2 + 2*X - 2*Y + 3)

surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
                       linewidth=0, antialiased=False)
plt.show()

plt.style.use('_mpl-gallery-nogrid')
levels = np.linspace(Z.min(), Z.max(), 15)
fig, ax = plt.subplots()
ax.contourf(X, Y, Z, levels=levels, cmap=cm.coolwarm, antialiased=False)
plt.show()

def equations(vars):
    x, y = vars
    eq1 = 6*x + (2*x + 2) / (x**2 + y**2 + 2*x - 2*y + 3)
    eq2 = 2*y + (2*y - 2) / (x**2 + y**2 + 2*x - 2*y + 3)
    return [eq1, eq2]

x, y = optimize.fsolve(equations, (-0.1, 0.3), xtol=eps)
print(f'x = {x:.6f}')
print(f'y = {y:.6f}')

A = 6 + (-2*x**2 + 2*y**2 - 4*x - 4*y + 2) / (x**2 + y**2 + 2*x - 2*y + 3)**2
B = -(2*x + 2) * (2*y - 2) / (x**2 + y**2 + 2*x - 2*y + 3)**2
C = 2 + (2*x**2 - 2*y**2 + 4*x + 4*y + 2) / (x**2 + y**2 + 2*x - 2*y + 3)**2

print(f'A = {A:.6f}')
print(f'B = {B:.6f}')
print(f'C = {C:.6f}')

D = A*C - B**2
print(f'D = {D:.6f}')