import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import approximate_taylor_polynomial
from prettytable import PrettyTable

def f(x, t):
    return 6*t - np.cos(x)*6*x

def lu(u: np.array, x: np.linspace, t: np.linspace, 
       i, k, h):
    return np.cos(x[i]) * (u[i + 1, k] - 2 * u[i, k] + u[i - 1, k]) / pow(h, 2)

def lphi(phi, x):
    return approximate_taylor_polynomial(phi, 0, 2, 1)(x)

def solve(h, tau):
    x_min = 0
    x_max = 1
    xs = np.arange(x_min, x_max + h, h)
    n_x = len(xs)

    t_min = 0
    t_max = 1
    ts = np.arange(t_min, t_max + tau, tau)
    n_t = len(ts)

    phi = lambda x: x**3
    psi = lambda x: 0
    alpha = lambda t: t**3
    beta = lambda t: 3

    U = np.zeros((n_x, n_t))
    U[:, 0] = [phi(x) for x in xs]
    U[:, 1] = [tau * psi(x) + phi(x) + tau**2 / 2 * (lphi(phi, x) * f(x, 0)) for x in xs]

    for k in range(1, n_t - 1):
        for i in range(1, n_x - 1):
            U[i, k + 1] = 2*U[i, k] - U[i, k - 1] + \
                tau**2*(lu(U, xs, ts, i, k, h) + f(xs[i], ts[k]))

        U[0, k + 1] = alpha(ts[k+1])
        U[-1, k + 1] = (2*h*beta(ts[k+1]) + 4*U[-2, k+1] - U[-3, k+1]) / 3
            
    return [xs, ts, U]

def makeTableFromResult(xs, ts, U):
    table = PrettyTable()
    ts = ts.round(3)
    xs = xs.round(3)
    U = U.round(3)
    table.add_column("x \ t", xs)
    for k in range(len(ts)):
        table.add_column(f"{ts[k]}", U[:, k])
    return table

h = 0.25
tau = 0.01

[xs, ts, U] = solve(h, tau)

print("Результат:")
print(makeTableFromResult(xs, ts, U))

fig = plt.figure()
ax = plt.axes(projection='3d')
X, Y = np.meshgrid(ts, xs)
ax.plot_surface(X, Y, U, rstride=1, cstride=1,
    cmap='viridis', edgecolor='none')
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

hs = []
taus = []
exact_diff = []
last_diff = []

[_, _, last_u] = solve(h, tau)
last_u = last_u[0::2]

for i in range(4):
    [xs, ts, U] = solve(h, tau)

    u = lambda t, x: x**3 + t**3
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

print(makeTableFromStep(hs, taus, last_diff, exact_diff))