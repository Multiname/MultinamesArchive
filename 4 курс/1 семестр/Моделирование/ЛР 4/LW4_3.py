import itertools
from functools import reduce

import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import sympy
from matplotlib.ticker import MultipleLocator

if __name__ == '__main__':
    conditions = [
        lambda x_1, x_2: 2 * x_1 + 5 * x_2 >= 12,
        lambda x_1, x_2: 5 * x_1 + 2 * x_2 >= 14,
        lambda x_1, x_2: x_1 >= 3,
        lambda x_1, x_2: x_2 >= 2
    ]

    equalities = [
        lambda x_1, x_2: 2 * x_1 + 5 * x_2 - 12,
        lambda x_1, x_2: 5 * x_1 + 2 * x_2 - 14,
        lambda x_1, x_2: x_1 - 3,
        lambda x_1, x_2: x_2 - 2
    ]

    labels = [
        '$2 x_1 + 5 x_2 >= 12$',
        '$5 x_1 + 2 x_2 >= 14$',
        '$x_1 >= 3$',
        '$x_2 >= 2$'
    ]

    colors = ['g', 'b', 'r', 'm']

    x_1_bounds = (-1, 7)
    x_2_bounds = (-1, 8)

    x_1_range = np.linspace(x_1_bounds[0], x_1_bounds[1], 250)
    x_2_range = np.linspace(x_2_bounds[0], x_2_bounds[1], 250)
    x_1s, x_2s = np.meshgrid(x_1_range, x_2_range)

    axis: plt.Axes
    figure, axis = plt.subplots()

    axis.set_xlim(*x_1_bounds)
    axis.set_ylim(*x_2_bounds)

    handles = []
    for equality in equalities:
        axis.contour(
            x_1s, x_2s, equality(x_1s, x_2s), [0],
            colors=colors[equalities.index(equality)]
        )
        handles.append(
            matplotlib.lines.Line2D(
                [], [], color=colors[equalities.index(equality)],
                marker="s", ls="",
                label=labels[equalities.index(equality)]
            )
        )

    regions = [condition(x_1s, x_2s) for condition in conditions]
    intersection = np.array(reduce(lambda _x, _y: _x & _y, regions))

    extent = (x_1s.min(), x_1s.max(), x_2s.min(), x_2s.max())
    plt.imshow(
        intersection.astype(int),
        extent=extent,
        origin="lower",
        cmap="Blues",
        alpha=0.25
    )

    plt.xlabel("$x_1$")
    plt.ylabel("$x_2$")

    axis.xaxis.set_major_locator(MultipleLocator(1))
    axis.yaxis.set_major_locator(MultipleLocator(1))

    axis.grid(color='w', linestyle='-')

    plt.legend(handles=handles)
    plt.show()

    sym_x_1 = sympy.Symbol('x_1')
    sym_x_2 = sympy.Symbol('x_2')
    for equality_1, equality_2 in list(itertools.combinations(equalities, 2)):

        solution = sympy.solve(
            [
                equality_1(sym_x_1, sym_x_2), equality_2(sym_x_1, sym_x_2)
            ],
            [sym_x_1, sym_x_2], particular=True
        )

        x_1 = solution[sym_x_1]
        x_2 = solution[sym_x_2]

        if all(ineq(x_1, x_2) for ineq in conditions):
            print('Пересечение графиков ', end='')
            print(labels[equalities.index(equality_1)], end=' и ')
            print(labels[equalities.index(equality_2)])
            print(solution)
