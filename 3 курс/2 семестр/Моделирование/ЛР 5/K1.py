# p(x, y) = 2
# q(x, y) = 1
import numpy as np
import matplotlib.pyplot as plt
from prettytable import PrettyTable

f_p = lambda x = None, y = None: 1 + x/2
f_q = lambda x = None, y = None: 1
f_f = lambda x, y: -6*x*y - 2*x - y**2*(y + 1)/2
f_mu = lambda x, y: x*y**2*(1 + y)

l_x = 1
l_y = 1

c_1 = 1
c_2 = 1.5
d_1 = 1
d_2 = 1

f_u_exact = lambda x, y: x*y**2*(1 + y)

f_u = lambda x, y, h_x, h_y, last_u, u, i, j: \
    ((f_p(x - h_x/2, y) * u[i - 1, j] \
      + f_p(x + h_x/2, y) * last_u[i + 1, j]
      )/ pow(h_x, 2) \
    + (f_q(x, y - h_y/2) * u[i, j - 1] \
       + f_q(x, y + h_y/2) * last_u[i, j + 1]) / pow(h_y, 2)\
    + f_f(x, y)) \
    / ((f_p(x - h_x/2, y) + f_p(x + h_x/2, y)) / pow(h_x, 2) \
       + (f_q(x, y - h_y/2) + f_q(x, y + h_y/2)) / pow(h_y, 2))

l_u = lambda x, y, u, i, j, h_x, h_y: \
    f_p(x + h_x/2, y) * (u[i + 1, j] - u[i, j]) / pow(h_x, 2) \
    - f_p(x - h_x/2, y) * (u[i, j] - u[i - 1, j]) / pow(h_x, 2) \
    + f_q(x, y + h_y/2) * (u[i, j + 1] - u[i, j]) / pow(h_y, 2) \
    - f_q(x, y - h_y/2) * (u[i, j] - u[i, j - 1]) / pow(h_y, 2)


M = 20
N = M

u_0 = np.zeros((N, M))
u_0_diff = 0
u = np.zeros((N, M))
xs = np.linspace(0, l_x, N)
ys = np.linspace(0, l_y, M)

print(ys[-1])
print(xs[-1])

h_x = (xs[1] - xs[0]) / 2
h_y = (ys[1] - ys[0]) / 2

k_list = []
exact_diff = []
last_diff = []
rel_d = []
rel_error = []
discrepancies = []


u_exact = np.array([[f_u_exact(x, y) for x in xs] for y in ys])

k = 0
eps = 5e-2
k_max = np.log(1/eps) / 4 / eps

LU = np.zeros((N, M))
F = np.zeros((N, M))

for i in range(1, N-1):
    for j in range(1, M-1):
        LU[i, j] = l_u(xs[i], ys[j], u_exact, i, j, h_x, h_y)
        F[i, j] = f_f(xs[i], ys[j]) 

print(f'|| F-Au^* || = {np.amax(np.abs(LU + F))}')

u = np.zeros((N, M))
LU = np.zeros((N, M))
F = np.zeros((N, M))

last_u = np.copy(u)

u[:, 0] = f_mu(xs, 0)
u[:, -1] = f_mu(xs, l_x)
u[0, :] = f_mu(0, ys)
u[-1, :] = f_mu(l_y, ys)
for i in range(1, N-1):
    for j in range(1, M-1):
        u[i, j] = f_u(xs[i], ys[j], h_x, h_y, last_u, u, i, j)

for i in range(1, N-1):
    for j in range(1, M-1):
        LU[i, j] = l_u(xs[i], ys[j], u, i, j, h_x, h_y)
        F[i, j] = f_f(xs[i], ys[j]) 

discrepancy_0 = np.amax(np.abs(LU + F))

print(f'|| F-AU^0 || = {discrepancy_0}')


u = np.zeros((N, M))

while len(exact_diff) == 0 or exact_diff[-1] > eps:
    last_u = np.copy(u)

    u[:, 0] = f_mu(xs, 0)
    u[:, -1] = f_mu(xs, l_x)
    u[0, :] = f_mu(0, ys)
    u[-1, :] = f_mu(l_y, ys)
    

    for i in range(1, N-1):
        for j in range(1, M-1):
            u[i, j] = f_u(xs[i], ys[j], h_x, h_y, last_u, u, i, j)

    LU = np.zeros((N, M))
    F = np.zeros((N, M))

    for i in range(1, N-1):
        for j in range(1, M-1):
            LU[i, j] = l_u(xs[i], ys[j], u, i, j, h_x, h_y)
            F[i, j] = f_f(xs[i], ys[j]) 

    if k == 0:
        u_0 = np.copy(u)
        u_0_diff = np.amax(np.abs(u_0 - u_exact))

    k_list.append(k)
    exact_diff.append(np.amax(np.abs(u - u_exact)))
    last_diff.append(np.amax(np.abs(u - last_u)))
    rel_error.append(np.amax(np.abs(u - u_exact))/u_0_diff)
    discrepancies.append(np.amax(np.abs(LU + F)))
    rel_d.append(discrepancies[-1] / discrepancy_0)

    k += 1

table = PrettyTable()
table.add_column("k", np.array(k_list).round(4))
table.add_column("|| F - AU^k ||", np.array(discrepancies).round(4))
table.add_column("rel.d", np.array(rel_d).round(4))
table.add_column("|| U^{k}-U_{exact} ||", np.array(exact_diff).round(4))
table.add_column("rel.error", np.array(rel_error).round(4))
table.add_column("|| U^{k}-U_{k-1} ||", np.array(last_diff).round(4))
print(table)


xs = np.linspace(0, l_x, 6)
ys = np.linspace(0, l_y, 6)
h_x = (xs[1] - xs[0]) / 2
h_y = (ys[1] - ys[0]) / 2
U = np.zeros((6, 6))


for k in range(130):
    last_u = np.copy(U)

    U[:, 0] = f_mu(xs, 0)
    U[:, -1] = f_mu(xs, l_x)
    U[0, :] = f_mu(0, ys)
    U[-1, :] = f_mu(l_y, ys)
    

    for i in range(1, 5):
        for j in range(1, 5):
            U[i, j] = f_u(xs[i], ys[j], h_x, h_y, last_u, U, i, j)

table = PrettyTable()
xs = xs.round(5)
ys = ys.round(5)
U = U.round(5)
table.add_column("y \ x", ys)
for k in range(len(xs)):
    table.add_column(f"{xs[k]}", U[:, k])

print("Решение на крупной сетке")
print(table)

u_exact = np.array([[f_u_exact(x, y) for x in xs] for y in ys])
table = PrettyTable()
xs = xs.round(5)
ys = ys.round(5)
u_exact = u_exact.round(5)
table.add_column("y \ x", ys)
for k in range(len(xs)):
    table.add_column(f"{xs[k]}", u_exact[:, k])

print("Точное решение на крупной сетке")
print(table)

    
fig = plt.figure()
ax = plt.axes(projection='3d')
X, Y = np.meshgrid(xs, ys)
ax.plot_surface(X, Y, U, rstride=1, cstride=1,
    cmap='viridis', edgecolor='none')
ax.set_xlabel('$x$')
ax.set_ylabel('$y$')
ax.set_zlabel('$u$')
plt.show()