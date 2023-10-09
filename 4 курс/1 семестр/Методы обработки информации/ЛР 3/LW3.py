import numpy as np
import matplotlib.pyplot as plt

sample_size = 100
p = 0.6
sample = np.random.geometric(p, size=sample_size)

p_estimate_1 = 1 / np.mean(sample)
print("Оценка параметра p:", p_estimate_1)

def likelihood(p, sample):
    likelihood = np.prod(p * (1-p)**(sample-1))
    return likelihood

grid = np.linspace(0.01, 1, 100) 
likelihood_values = [likelihood(p_val, sample) for p_val in grid]
p_estimate_2 = grid[np.argmax(likelihood_values)]
print("Оценка параметра p:", p_estimate_2)

plt.plot(grid, likelihood_values)
plt.axvline(p_estimate_1, color='r', linestyle='--', label='Метод моментов')
plt.axvline(p_estimate_2, color='g', linestyle=':', label='Метод максимального правдоподобия')
plt.legend()
plt.show()