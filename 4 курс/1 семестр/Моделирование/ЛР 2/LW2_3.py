import numpy as np
import matplotlib.pyplot as plt

X = np.linspace(0, 2000, 2001)

days = 5
hours = 8
Y_1 = (25*days*hours*60 - 20*X) / 60
Y_2 = (35*days*hours*60 - 70*X) / 60
Y_3 = (5*days*hours*60 - 12*X) / 4

fig, ax = plt.subplots()
ax.set_ylim(0, 2000)

ax.fill([0,         X[0],   X[-1],      X[-1]], 
        [Y_3[-1],   Y_1[0], Y_1[-1],    Y_3[-1]], 
        'blue', alpha=0.33)
ax.fill([0,         X[0],   X[-1],      X[-1]], 
        [Y_3[-1],   Y_2[0], Y_2[-1],    Y_3[-1]], 
        'blue', alpha=0.33)
ax.fill([0,         X[0],   X[-1],      X[-1]], 
        [Y_3[-1],   Y_3[0], Y_3[-1],    Y_3[-1]], 
        'blue', alpha=0.33)

ax.plot(X, Y_1, 'k--', label='20x₁ + 60x₂ ≤ 25∙5∙8∙60')
ax.plot(X, Y_2, 'k-.', label='70x₁ + 60x₂ ≤ 35∙5∙8∙60')
ax.plot(X, Y_3, 'k:', label='12x₁ + 4x₂ ≤ 5∙5∙8∙60')

Y_1_min = (444000/11 - 20*X) / 60
Y_1_max = (84000 - 20*X) / 60
Y_2_min = (70000 - 70*X) / 60
Y_2_max = (97500 - 70*X) / 60
Y_3_min = (9120 - 12*X) / 4
Y_3_max = (14400 - 12*X) / 4

# ax.plot(X, Y_1_min, 'm--', label='M₁ = 444000 / 11')
# ax.plot(X, Y_1_max, 'r--', label='M₁ = 84000')
# ax.plot(X, Y_2_min, 'm-.', label='M₂ = 70000')
# ax.plot(X, Y_2_max, 'r-.', label='M₂ = 97500')
# ax.plot(X, Y_3_min, 'm:', label='M₃ = 9120')
# ax.plot(X, Y_3_max, 'r:', label='M₃ = 14400')

Y_1_ot = (180000 - 20*X) / 60
Y_2_ot = (180000 - 70*X) / 60

# ax.plot(X, Y_1_ot, 'm--', label='M₁ = 180000')
# ax.plot(X, Y_2_ot, 'm-.', label='M₂ = 180000')

# ax.plot(2000, 3000, 'rx')
# ax.text(2000 - 500, 3000 - 200, 'K(2000; 3000)', fontsize=8)

ax.plot(480, 840, 'ko')
ax.plot(9600/11, 4200/11, 'ko')
ax.plot(0, 35*5*8, 'ko')
ax.plot(0, 25*5*8, 'ko')
ax.plot(5*5*8*5, 0, 'ko')
ax.plot(5*5*8*6, 0, 'ko')
ax.plot(750, 750, 'ko')
ax.plot(0, 3000, 'ko')

ax.text(480 + 50, 840 + 25, 'C(480; 840)', fontsize=8)
ax.text(9600/11 - 400, 4200/11 - 25, f'E({9600/11:.2f}; {4200/11:.2f})', fontsize=8)
ax.text(0 + 20, 35*5*8 + 50, f'A(0; {35*5*8})', fontsize=8)
ax.text(0 + 25, 25*5*8 + 30, f'B(0; {25*5*8})', fontsize=8)
ax.text(5*5*8*5 - 250, 0 + 50, f'F({5*5*8*5}; 0)', fontsize=8)
ax.text(5*5*8*6 + 50, 0 + 50, f'G({5*5*8*6}; 0)', fontsize=8)
ax.text(750 + 50, 750, f'D(750; 750)', fontsize=8)
ax.text(0 + 50, 3000, f'H(0; 3000)', fontsize=8)

F = 3888
Y = (F - 2.5*X) / 3.2
# ax.plot(X, Y, 'r', label='2.5x₁ + 3.2x₂ = 3888')

F_ot = 9600
Y_ot = (F_ot - 2.5*X) / 3.2
# ax.plot(X, Y_ot, 'm', label='2.5x₁ + 3.2x₂ = 9600')

F_min = 3000
F_max = 3888
Y_min = (F_min - 2.5*X) / 3.2
Y_max = (F_max - 2.5*X) / 3.2
# ax.plot(X, Y_min, 'm', label='Fₘᵢₙ = 3000')
# ax.plot(X, Y_max, 'r', label='Fₘₐₓ = 3888')

plt.gca().set_aspect('equal')

ax.legend()
plt.show()