import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import scipy.linalg as la
from prettytable import PrettyTable

def f(x, t):
    return 3*t**2 - 20*x**3 + (x**5 + t**3)*np.sin(x)

def lu(u: np.array, x: np.linspace, t: np.linspace, 
       i, k, h):
     return (u[i + 1, k] - 2 * u[i, k] + u[i - 1, k]) / pow(h, 2) - u[i, k]*np.sin(x[i])

def solve(h, tau, sigma):
    x_min = 0
    x_max = 1
    xs = np.arange(x_min, x_max + h, h)
    n_x = len(xs)

    t_min = 0
    t_max = 0.1
    ts = np.arange(t_min, t_max + tau, tau)
    n_t = len(ts)

    phi = lambda x, t: pow(x, 5)
    alpha = lambda t: pow(t, 3)
    beta = lambda t: pow(t, 3) + 6

    U = np.zeros((n_x, n_t))
    G = np.zeros((n_x, n_t))
    U[:, 0] = [phi(x, t_min) for x in xs]
    A = np.zeros((n_x - 1))
    B = np.zeros((n_x))
    C = np.zeros((n_x - 1))

    G[0, 0] = h*alpha(ts[0])
    G[-1, 0] = h*beta(ts[0])

    for k in range(0, n_t - 1):
        for i in range(1, n_x - 1):
            G[i, k+1] = (-1 * U[i, k]) / tau \
                - (1 - sigma) * lu(U, xs, ts, i, k, h) \
                - f(xs[i], ts[k])
            A[i - 1] = sigma / h**2
            B[i] = 2*sigma / h**2 + np.sin(xs[i]) + 1 / tau
            C[i] = sigma / h**2
  
        B[0] = -(h + 1)
        C[0] =  -1
        A[-1] = -1
        B[-1] = -(h + 1)

        G[0, k+1] = h*alpha(ts[k+1])
        G[-1, k+1] = h*beta(ts[k+1])
        
        matrix = np.array([[0, *C], B, [*A, 0]])
        
        U[:, k+1] = la.solve_banded((1,1), matrix, G[:, k+1])
        
    return [xs, ts, U]

def makeTableFromResult(xs, ts, U):
    table = PrettyTable()
    ts = ts.round(4)
    xs = xs.round(4)
    U = U.round(5)
    table.add_column("x \ t", xs)
    for k in range(len(ts)):
        table.add_column(f"{ts[k]}", U[:, k])
    return table

h = 0.25
tau = 0.01
sigma = 0.5

[xs, ts, U] = solve(h, tau, sigma)

fig = plt.figure()
ax = plt.axes(projection='3d')
X, Y = np.meshgrid(ts, xs)
ax.plot_surface(X, Y, U, rstride=1, cstride=1,
    cmap='magma', edgecolor='none')
ax.set_xlabel('$t$')
ax.set_ylabel('$x$')
ax.set_zlabel('$u$')
plt.show()

def makeTableFromStep(hs, taus, diff, exact_diff):
    table = PrettyTable()
    table.add_column("h", hs)
    table.add_column("tau", taus)
    table.add_column("||U_{exact}-U_{h}||", diff)
    table.add_column("||U_{2h}-U_{h}}||", exact_diff)
    return table

def makeTableFromResult(xs, ts, U):
    table = PrettyTable()
    ts = ts.round(3)
    xs = xs.round(3)
    U = U.round(3)
    table.add_column("x \ t", xs)
    for k in range(len(ts)):
        table.add_column(f"{ts[k]}", U[:, k])
    return table

[xs, ts, U] = solve(h, tau, sigma)

print("Результат:")
print(makeTableFromResult(xs, ts, U))

hs = []
taus = []
exact_diff = []
last_diff = []

[_, _, last_u] = solve(h, tau, sigma)
last_u = last_u[0::2]

for i in range(3):
    [xs, ts, U] = solve(h, tau, sigma)

    u = lambda t, x: x**5 + t**3
    U_exact = np.array([[u(t, x) for t in ts] for x in xs])

    hs.append(h)
    taus.append(tau)
    exact_diff.append(np.amax(np.abs(U - U_exact)))
    last_diff.append(np.amax(np.abs(last_u - U[0::2])))
    
    h /= 2
    last_u = U

hs = np.array(hs).round(5)
taus = np.array(taus).round(5)
exact_diff = np.array(exact_diff).round(5)
last_diff = np.array(last_diff).round(5)

print(makeTableFromStep(hs, taus, exact_diff, last_diff))