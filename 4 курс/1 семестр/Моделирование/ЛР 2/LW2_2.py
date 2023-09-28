import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

X = np.linspace(-1.5, 1.5, 100)

Y_1 = np.sqrt(9 - 4*X**2) / 6
Y_2 = -np.sqrt(9 - 4*X**2) / 6

fig, ax = plt.subplots()
ax.plot(X, Y_1, 'r', label='4x₁² + 36x₂² = 9')
ax.plot(X, Y_2, 'r')

z_line, = ax.plot([], [], 'b', label='z = 4x₁ + 9x₂ - 25')
dots, = ax.plot([], [], 'o')
z_text = ax.text(-1.4, 0.8, '', fontsize=10)
min_text = ax.text(-1.15, -0.25, '', fontsize=10)
max_text = ax.text(0.7, 0.1, '', fontsize=10)

x_dots = []
y_dots = []
min_is_placed = False
max_is_placed = False

def init():
    ax.set_xlim(-1.5, 1.5)
    ax.set_ylim(-1.0, 1.0)
    return z_line, dots, z_text, min_text, max_text,

def update(frame):
    global x_dots
    global y_dots
    global min_is_placed
    global max_is_placed

    z_line.set_data(X, (frame - 4*X + 25) / 9)

    if not min_is_placed and frame == -32.5:
        x_dots.append(-1.2)
        y_dots.append(-0.3)
        min_text.set_text(f'z = -32.5\nM₁(-1.2, -0.3)')
    if not max_is_placed and frame == -17.5:
        x_dots.append(1.2)
        y_dots.append(0.3)
        max_text.set_text(f'z = -17.5\nM₂(1.2, 0.3)')
    dots.set_data(x_dots, y_dots)

    z_text.set_text(f'z = {frame:.2f}')

    return z_line, dots, z_text, min_text, max_text,

ani = FuncAnimation(fig, update, frames=np.linspace(-35, -15, 401),
                    init_func=init, blit=True, interval=5)
ax.legend()
plt.show()