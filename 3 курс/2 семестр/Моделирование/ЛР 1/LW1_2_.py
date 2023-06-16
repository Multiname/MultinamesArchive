import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_bvp, solve_ivp
import scipy.linalg as la

def g(x):
        return -(5 - x)/(7 - 3*x)

def task(a2, a1, a0, g, robin_A, robin_B, rng, h):
    n = int((rng[1]-rng[0])/h) + 1

    pf = lambda x: 1 - a1(x)/a2(x) * h / 2
    qf = lambda x: -(2 - a0(x)/a2(x) * h**2)
    rf = lambda x: 1 + a1(x)/a2(x) * h / 2
    df = lambda x: g(x)/a2(x) * h**2

    xs = np.linspace(rng[0], rng[1], n)
    A = np.zeros((n, n))
    B = np.zeros(n)

    A[n-1, n-2] = robin_A[1, 1] * (pf(xs[n-1]) + rf(xs[n-1]))
    A[n-1, n-1] = robin_A[1, 1] * qf(xs[n-1]) - 2 * h * robin_A[1, 0]
    B[n-1] = df(xs[n-1]) * robin_A[1, 1] - 2 * h * robin_B[1] * pf(xs[n-1])

    #xn = xs[n-1]
    #A[n-1, n-1] = robin_A[1, 1] * qf(xn) - 2 * h * robin_A[1, 0]
    #A[n-1, n-2] = robin_A[1, 1] * (pf(xn) + rf(xn))
    #B[n-1] = df(xn) * robin_A[1, 1] - 2 * h * robin_B[1] * pf(xn)

    #pf = lambda x: 2*a2(x) - a1(x)*h
    #qf = lambda x: -4*a2(x) + 2*a0(x)*h**2
    #rf = lambda x: 2*a2(x) + a1(x)*h
    #df = lambda x: 2*g(x) * h**2

    A[0, 1] = qf(xs[0]) + rf(xs[0])
    A[0, 0] = pf(xs[0])
    B[0] = df(xs[0]) - rf(xs[0])*0*h

    for i in range(1, n - 1):
         A[i, i - 1] = pf(xs[i])
         A[i, i] = qf(xs[i])
         A[i, i + 1] = rf(xs[i])
         B[i] = df(xs[i])

    u = np.linalg.solve(A, B)
    
    return xs, u

def exact_task(rng):
    a = -1
    b = 1

    def fun(x, y):
        return np.vstack((y[1], ((1 - x)/2*y[1] - (1 + 0.5*np.sin(x))*y[0] + (1/2 + x/2))/g(x)))

    def bc(ya, yb):
        return np.array([ya[1], 2*yb[1] + 3*yb[0]])
    

    res = solve_bvp(fun, bc, [a, b], [[-1, -1], [1, 1]], tol=1e-9)

    return res.x, res.y[0], res

if __name__ == "__main__":
    h = 0.01
    rng = [-1, 1]

    tol = 1e-3
    cnt = 3
    err = tol + 1

    x_ex, y_ex, res = exact_task(rng)

    x, y = task(a2 = lambda x: -(5 - x)/(7 - 3*x),
            a1 = lambda x: -(1 - x)/2,
            a0 = lambda x: 1 + 0.5*np.sin(x),
            g  = lambda x: 1/2 + x/2,
            robin_A = np.array([[-2, 1], [3, 2]]), 
            robin_B = np.array([0, 0]), 
            rng=rng, 
            h=h)

    print(f"\nЛабораторная работа 1.2\n")
    print(f"┏{'━'*30}┳{'━'*30}┓")
    print(f"┃{'Шаг':>29} ┃{'Погрешность':>29} ┃")
    print(f"┣{'━'*30}╋{'━'*30}┫")

    while err >= tol:
        x, y = task(a2 = lambda x: -(5 - x)/(7 - 3*x),
            a1 = lambda x: -(1 - x)/2,
            a0 = lambda x: 1 + 0.5*np.sin(x),
            g  = lambda x: 1/2 + x/2,
            robin_A = np.array([[-2, 1], [3, 2]]), 
            robin_B = np.array([0, 0]), 
            rng=rng, 
            h=h)
        err = round(max(abs(np.array([res.sol(i)[0] for i in x]) - y)), cnt)
        h /= 2
        print(f'┃{round(h, 10):29.10f} ┃{err:29.5f} ┃')

    print(f"┗{'━'*30}┻{'━'*30}┛")

    print(f'\n{f"Точное значение в точке {rng[0]}:":40} {res.sol(rng[0])[0]}')
    print(f'{f"Полученное значение в точке {rng[0]}:":40} {y[0]}')

    print(f'\n{f"Точное значение в точке {rng[1]}:":40} {res.sol(rng[1])[0]}')
    print(f'{f"Полученное значение в точке {rng[1]}:":40} {y[-1]}')

    print(f'\n{f"Точность:":40} {tol}')
    print(f'{f"Значение шага:":40} {h}')

    plt.subplot(2, 1, 1)
    plt.plot(x, y, color='#801010', label='$u_{прибл}(x)$')
    plt.grid(alpha=0.5)
    plt.legend(framealpha=1, shadow=True)

    plt.subplot(2, 1, 2)
    plt.plot(res.x, res.y[0], color='#801010', label='$u_{точн}(x)$')
    plt.grid(alpha=0.5)
    plt.legend(framealpha=1, shadow=True)
    plt.show()