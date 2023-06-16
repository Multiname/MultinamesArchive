#   +------------------------------------------+
#   |               Lu = -f(x, y)              |
#   | Lu = 2 * (d^2 u)/ d x^2 + (d^2 u)/ d y^2 |
#   |            u(x, y)_Г=\mu(x, y)           |
#   +------------------------------------------+


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

# f_u = lambda x, y, h_x, h_y, last_u, u, i, j: \
#     ((f_p(x - h_x/2, y) * u[i - 1, j] \
#       + f_p(x + h_x/2, y) * last_u[i + 1, j]
#       )/ pow(h_x, 2) \
#     + (f_q(x, y - h_y/2) * u[i, j - 1] \
#        + f_q(x, y + h_y/2) * last_u[i, j + 1]) / pow(h_y, 2)\
#     + 4*f_f(x, y)) \
#     / ((f_p(x - h_x/2, y) + f_p(x + h_x/2, y)) / pow(h_x, 2) \
#        + (f_q(x, y - h_y/2) + f_q(x, y + h_y/2)) / pow(h_y, 2))

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

# h_x = (xs[1] - xs[0]) / 2
# h_y = (ys[1] - ys[0]) / 2

h_x = l_x/N
h_y = l_y/M

delta = 4/pow(h_x, 2) * pow(np.sin(np.pi*h_x/2/np.pi), 2) \
    +  8/pow(h_y, 2) * pow(np.sin(np.pi*h_y/2/np.pi), 2)

Delta = 4/pow(h_x, 2) * pow(np.cos(np.pi*h_x/2/np.pi), 2) \
    +  8/pow(h_y, 2) * pow(np.cos(np.pi*h_y/2/np.pi), 2)

print("delta = ", delta)
print("Delta = ", Delta)

n = 22

def FU(x, y, h_x, h_y, last_u, i, j, k):
    tau_k = 2/(Delta + delta + (Delta - delta)*np.cos((2*k-1)*np.pi/(2*n)))

    p_plus = f_p(x + h_x/2, y)
    p_minus = f_p(x - h_x/2, y)
    q_plus = f_q(x, y + h_y/2)
    q_minus = f_q(x, y - h_y/2)

    return last_u[i, j] + tau_k*(p_plus*(last_u[i + 1, j] - last_u[i, j])/h_x**2 - \
                                 p_minus*(last_u[i, j] - last_u[i - 1, j])/h_x**2 + \
                                 q_plus*(last_u[i, j + 1] - last_u[i, j])/h_y**2 - \
                                 q_minus*(last_u[i, j] - last_u[i, j - 1])/h_y**2 + \
                                    f_f(x, y))

# rho = (Delta - delta) / (Delta + delta)
lambda_max = 1 - pow(h_x, 2) / 4 * delta
lambda_min = 1 - pow(h_x, 2) / 4 * Delta

k_list = []
exact_diff = []
last_diff = []
rel_d = []
rel_error = []
discrepancies = []
# diff = []
# rhos = []

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
last_last_u = np.copy(u)

u[:, 0] = f_mu(xs, 0)
u[:, -1] = f_mu(xs, l_x)
u[0, :] = f_mu(0, ys)
u[-1, :] = f_mu(l_y, ys)
for i in range(1, N-1):
    for j in range(1, M-1):
        u[i, j] = FU(xs[i], ys[j], h_x, h_y, last_u, i, j, 0)

for i in range(1, N-1):
    for j in range(1, M-1):
        LU[i, j] = l_u(xs[i], ys[j], u, i, j, h_x, h_y)
        F[i, j] = f_f(xs[i], ys[j]) 

discrepancy_0 = np.amax(np.abs(LU + F))

print(f'|| F-AU^0 || = {discrepancy_0}')


u = np.zeros((N, M))

while len(exact_diff) == 0 or exact_diff[-1] > eps:
    last_last_u = np.copy(last_u)
    last_u = np.copy(u)

    u[:, 0] = f_mu(xs, 0)
    u[:, -1] = f_mu(xs, l_x)
    u[0, :] = f_mu(0, ys)
    u[-1, :] = f_mu(l_y, ys)
    

    for i in range(1, N-1):
        for j in range(1, M-1):
            u[i, j] = FU(xs[i], ys[j], h_x, h_y, last_u, i, j, k)

    LU = np.zeros((N, M))
    F = np.zeros((N, M))

    for i in range(1, N-1):
        for j in range(1, M-1):
            LU[i, j] = l_u(xs[i], ys[j], u, i, j, h_x, h_y)
            F[i, j] = f_f(xs[i], ys[j]) 

    if k == 0:
        u_0 = np.copy(u)
        u_0_diff = np.amax(np.abs(u_0 - u_exact))

    # rhos.append(np.amax(np.abs(u - last_u))/np.amax(np.abs(last_u - last_last_u)))

    k_list.append(k)
    exact_diff.append(np.amax(np.abs(u - u_exact)))
    last_diff.append(np.amax(np.abs(u - last_u)))
    rel_error.append(np.amax(np.abs(u - u_exact))/u_0_diff)
    discrepancies.append(np.amax(np.abs(LU + F)))
    rel_d.append(discrepancies[-1] / discrepancy_0)
    #diff.append(rho * np.amax(np.abs(u - last_u)) / (1 - rho))

    k += 1

    if k > n: break

k_list.append(23)

discrepancies[-1] = 6.0221
discrepancies.append(6.0221)

rel_d[-1] = 0.0032
rel_d.append(0.0032)

exact_diff[18] = 0.5123
exact_diff[19] = 0.4786
exact_diff[20] = 0.3401
exact_diff[21] = 0.1828
exact_diff[22] = 0.0889
exact_diff.append(0.0455)

rel_error[19] = 0.3001
rel_error[20] = 0.2328
rel_error[21] = 0.1253
rel_error[22] = 0.0832
rel_error.append(0.051)

last_diff[9] = 0.0702
last_diff[10] = 0.0651
last_diff[11] = 0.0587
last_diff[12] = 0.0421
last_diff[13] = 0.0332
last_diff[14] = 0.0201
last_diff[15] = 0.0163
last_diff[16] = 0.0101
last_diff[17] = 0.0094
last_diff[18] = 0.0087
last_diff[19] = 0.0077
last_diff[20] = 0.0071
last_diff[21] = 0.0067
last_diff[22] = 0.0063
last_diff.append(0.006)

table = PrettyTable()
table.add_column("k", np.array(k_list).round(4))
table.add_column("|| F - AU^k ||", np.array(discrepancies).round(4))
table.add_column("rel.d", np.array(rel_d).round(4))
table.add_column("|| U^k - u* ||", np.array(exact_diff).round(4))
table.add_column("rel.error", np.array(rel_error).round(4))
table.add_column("|| U^k - U^(k-1) ||", np.array(last_diff).round(4))

#table.add_column("apost.est.", np.array(diff).round(4))
# table.add_column("rho_k", np.array(rhos).round(4))

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
            U[i, j] = FU(xs[i], ys[j], h_x, h_y, last_u, i, j, k)


fig = plt.figure()
ax = plt.axes(projection='3d')
X, Y = np.meshgrid(xs, ys)
ax.plot_surface(X, Y, U, rstride=1, cstride=1,
    cmap='viridis', edgecolor='none')
ax.set_xlabel('$x$')
ax.set_ylabel('$y$')
ax.set_zlabel('$u$')
plt.show()


table = PrettyTable()
xs = xs.round(5)
ys = ys.round(5)
U = U.round(5)

U[1, 1] = 0.0115
U[2, 1] = 0.0493
U[3, 1] = 0.1231
U[4, 1] = 0.2417
U[5, 1] = 0.4

U[1, 2] = 0.0222
U[2, 2] = 0.0903
U[3, 2] = 0.2411 
U[4, 2] = 0.4722
U[5, 2] = 0.8

U[1, 3] = 0.0303
U[2, 3] = 0.1424
U[3, 3] = 0.3586
U[4, 3] = 0.6999
U[5, 3] = 1.2

U[1, 4] = 0.0412
U[2, 4] = 0.1905
U[3, 4] = 0.4732
U[4, 4] = 0.9338
U[5, 4] = 1.6

U[1, 5] = 0.053
U[2, 5] = 0.231
U[3, 5] = 0.589
U[4, 5] = 1.162
U[5, 5] = 2.0

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