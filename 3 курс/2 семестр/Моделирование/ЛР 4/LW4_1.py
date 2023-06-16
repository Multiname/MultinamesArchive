import numpy as np
import matplotlib.pyplot as plt
from prettytable import PrettyTable

def f(x, t):
    return 3*t**2 - 6*x + (x**3 + t**3)*np.sin(x)
    #return (x**2 + t)*np.sin(x) - 1

def lu(u: np.array, x: np.linspace, t: np.linspace, i, k, h):
     return (u[i + 1, k] - 2*u[i, k] + u[i - 1, k]) / pow(h, 2) - u[i, k]*np.sin(x[i])

def solve(h, tau):
    x_min = 0
    x_max = 1
    xs = np.arange(x_min, x_max + h, h)
    n_x = len(xs)

    t_min = 0
    t_max = 0.1
    ts = np.arange(t_min, t_max + tau, tau)
    n_t = len(ts)

    #phi = lambda x, t: x**2
    phi = lambda x, t: pow(x, 3)
    #alpha = lambda t: t
    alpha = lambda t: pow(t, 3)
    #beta = lambda t: t + 3
    beta = lambda t: 4 + pow(t, 3)

    U = np.zeros((n_x, n_t))
    U[:, 0] = [phi(x, t_min) for x in xs]

    for k in range(1, n_t):
        for i in range(1, n_x - 1):
            U[i, k] = U[i, k - 1] + tau * (lu(U, xs, ts, i, k - 1, h) +
                                           f(xs[i], ts[k - 1]))

        U[0, k] = (2*h*alpha(ts[k]) - 4*U[1, k] + U[2, k]) / (2*h + 3)
        U[-1, k] = (2*h*beta(ts[k]) + 4*U[-2, k] - U[-3, k]) / (2*h + 3)
    
    return [xs, ts, U]

def makeTableFromResult(xs, ts, U):
    table = PrettyTable()
    ts = ts.round(4)
    xs = xs.round(4)
    U = U.round(4)
    table.add_column("x \ t", xs)
    for k in range(len(ts)):
        table.add_column(f"{ts[k]}", U[:, k])
    return table

h = 0.125
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

def makeTableFromStep(hs, taus, exact_diff, diff):
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

for i in range(3):
    [xs, ts, U] = solve(h, tau)

    u = lambda t, x: x**3 + t**3
    #u = lambda t, x: x**2 + t
    U_exact = np.array([[u(t, x) for t in ts] for x in xs])

    hs.append(h)
    taus.append(tau)
    exact_diff.append(np.amax(np.abs(U - U_exact)))
    last_diff.append(np.amax(np.abs(last_u - U[0::2])))
    
    h /= 2
    last_u = U

hs = np.array(hs).round(7)
taus = np.array(taus).round(7)
exact_diff = np.array(exact_diff).round(7)
last_diff = np.array(last_diff).round(7)

print(makeTableFromStep(hs, taus, last_diff, exact_diff))