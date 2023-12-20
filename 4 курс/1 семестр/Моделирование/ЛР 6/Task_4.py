import matplotlib.pyplot as plt
import numpy as np

def linear_congruential_generator(a, m, c, R0, n):
    random_numbers = [R0]
    for _ in range(n - 1):
        next_number = (a * random_numbers[-1] + c) % m
        random_numbers.append(next_number)
    return random_numbers

def period_length(sequence):
    for i in range(1, len(sequence) // 2 + 1):
        if sequence[:i] == sequence[i:2*i]:
            return i
    return -1

def histogram_and_distribution_plot(data, bins, title):
    plt.figure(figsize=(12, 6))

    plt.subplot(1, 2, 1)
    plt.hist(data, bins=bins, density=True, alpha=0.75, color='skyblue', edgecolor='black')
    plt.title(title + ' - Histogram')
    plt.xlabel('Random Numbers')
    plt.ylabel('Probability')

    plt.subplot(1, 2, 2)
    plt.hist(data, bins=bins, density=True, cumulative=True, alpha=0.75, color='skyblue', edgecolor='black')
    plt.title(title + ' - Cumulative Distribution')
    plt.xlabel('Random Numbers')
    plt.ylabel('Cumulative Probability')

    plt.tight_layout()
    plt.show()

# Parameters
N_values = [10.7e6, 10.8e6, 10.9e6]
m_values = [27, 28, 29]
R0_values = [103, 107, 107]  # Choose different initial values

R0_labels = [103, 107, 109]

for N, m, R0, l in zip(N_values, m_values, R0_values, R0_labels):
    a = 7**5
    c = 0
    M = N

    # Generate random numbers
    random_sequence = linear_congruential_generator(a, M, c, R0, n=int(1e5))

    # Compute the period
    period = period_length(random_sequence)
    print(f"Period for N={N}, m({m}), R0={l}: {period}")

    # Plot histogram and distribution
    bins = np.linspace(0, M, num=100)
    histogram_and_distribution_plot(random_sequence, bins, f"N={N}, m({m}), R0={l}")