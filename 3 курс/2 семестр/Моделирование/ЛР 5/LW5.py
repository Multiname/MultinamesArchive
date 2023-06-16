# lu = 2 d^2u/dx^2 + d^2u/dy^2

# p(x, y) = 2
# q(x, y) = 1
import numpy as np
import matplotlib.pyplot as plt
from prettytable import PrettyTable



f_p = lambda x = None, y = None: 1 + x/2
f_q = lambda x = None, y = None: 1
f_f = lambda x, y: -6*x*y - 2*x
f_mu = lambda x, y: x*y**2*(1 + y)

l_x = 1
l_y = 1

c_1 = 1
c_2 = 1.5
d_1 = 1
d_2 = 1

f_u_exact = lambda x, y: x*y**2*(1 + y)

f_u = lambda x, y, h_x, h_y, last_u, u, i, j: \
    ((f_p(x - h_x/2, y) * u[i - 1, j]) / pow(h_x, 2) \
    + (f_p(x + h_x/2, y) * last_u[i + 1, j]) / pow(h_x, 2) \
    + (f_q(x, y - h_y/2) * u[i, j - 1]) / pow(h_y, 2) \
    + (f_q(x, y + h_y/2) * last_u[i, j + 1]) / pow(h_y, 2)\
    + f_f(x, y)) \
    / (f_p(x - h_x/2, y) / pow(h_x, 2) \
       + f_p(x + h_x/2, y) / pow(h_x, 2) \
       + f_q(x, y - h_y/2) / pow(h_y, 2)\
       + f_q(x, y + h_y/2) / pow(h_y, 2))

M = 20
N = M

u_0 = np.zeros((N, M))
u_0_diff = 0
u = np.zeros((N, M))
xs = np.linspace(0, l_x, N)
ys = np.linspace(0, l_y, M)

print(ys[-1])
print(xs[-1])

h_x = l_x/N
h_y = l_y/M

delta = c_1*4/h_x**2*np.sin(np.pi*h_x/(2*l_x))**2 + \
        d_1*4/h_y**2*np.sin(np.pi*h_y/(2*l_y))**2
DELTA = c_2*4/h_x**2*np.cos(np.pi*h_x/(2*l_x))**2 + \
        d_2*4/h_y**2*np.cos(np.pi*h_y/(2*l_y))**2
#n = int(np.ceil(np.log(2/1e-5)/(2*np.sqrt(delta / DELTA))))
n = 30

def FU(x, y, h_x, h_y, last_u, i, j, k):
    tau_k = 2/(DELTA + delta + (DELTA - delta)*np.cos((2*k-1)*np.pi/(2*n)))

    p_plus = f_p(x + h_x/2, y)
    p_minus = f_p(x - h_x/2, y)
    q_plus = f_q(x, y + h_y/2)
    q_minus = f_q(x, y - h_y/2)

    return last_u[i, j] + tau_k*(p_plus*(last_u[i + 1, j] - last_u[i, j])/h_x**2 - \
                                 p_minus*(last_u[i, j] - last_u[i - 1, j])/h_x**2 + \
                                 q_plus*(last_u[i, j + 1] - last_u[i, j])/h_y**2 - \
                                 q_minus*(last_u[i, j] - last_u[i, j - 1])/h_y**2 + \
                                    f_f(x, y))

k_list = []
exact_diff = []
last_diff = []
rel_d = []
rel_error = []

for k in range(n):
    last_u = np.copy(u)

    u[:, 0] = f_mu(xs, 0)
    u[:, -1] = f_mu(xs, l_x)
    u[0, :] = f_mu(0, ys)
    u[-1, :] = f_mu(l_y, ys)

    for i in range(1, N-1):
        for j in range(1, M-1):
            #u[i, j] = f_u(xs[i], ys[j], h_x, h_y, last_u, u, i, j)
            u[i, j] = FU(xs[i], ys[j], h_x, h_y, last_u, i, j, k)

    u_exact = np.array([[f_u_exact(x, y) for x in xs] for y in ys])

    if k == 0:
        u_0 = np.copy(u)
        u_0_diff = np.amax(np.abs(u_0 - u_exact))

    k_list.append(k)
    exact_diff.append(np.amax(np.abs(u - u_exact)))
    last_diff.append(np.amax(np.abs(u - last_u)))
    rel_error.append(np.amax(np.abs(u - u_exact))/u_0_diff)

table = PrettyTable()
table.add_column("k", np.array(k_list).round(4))
table.add_column("||U^{k}-U_{exact}||", np.array(exact_diff).round(4))
table.add_column("rel.error", np.array(rel_error).round(4))
table.add_column("||U^{k}-U_{k-1}||", np.array(last_diff).round(4))
print(table)


    
fig = plt.figure()
ax = plt.axes(projection='3d')
X, Y = np.meshgrid(xs, ys)
ax.plot_surface(X, Y, u, rstride=1, cstride=1,
    cmap='viridis', edgecolor='none')
ax.set_xlabel('$x$')
ax.set_ylabel('$y$')
ax.set_zlabel('$u$')
plt.show()