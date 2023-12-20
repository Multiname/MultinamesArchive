import random


# Гауссовское распределение с матожиданием 6 и СКО 1
def gauss_distribution(mu, sigma):
    return random.gauss(mu, sigma)


# Дискретное равномерное распределение в диапазоне 5-8
def uniform_distribution():
    return random.uniform(3, 6)


def simulate_service_station(num_shifts, service_time_distribution, interarrival_time_distribution):
    num_masters = 3
    total_clients = 0
    total_service_time = 0

    for shift in range(num_shifts):
        time_elapsed = 0
        clients_served = 0

        while time_elapsed < 480:  # Рабочая смена 8 часов (480 минут)
            # интервал между приездами двух клиентов
            interarrival_time = interarrival_time_distribution()

            # момент времени, когда прибывает новый клиент
            arrival_time = time_elapsed + interarrival_time

            # время обслуживания клиентов
            service_time = service_time_distribution()

            time_elapsed = arrival_time
            clients_served += 1
            total_service_time += service_time

            time_elapsed += service_time

        total_clients += clients_served

    average_service_time = total_service_time / total_clients / num_masters
    print(f"Смены: {num_shifts}")
    print(f"Среднее время: {average_service_time:.2f} минут")

mu = 4
sigma = 1

# Моделирование для различных комбинаций и отклонений
print('Гауссовское распределение')
simulate_service_station(num_shifts=1,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))

simulate_service_station(num_shifts=3,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))

simulate_service_station(num_shifts=10,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))

print()
###

print('Равномерного распределение')
simulate_service_station(num_shifts=1,
                         service_time_distribution=uniform_distribution,
                         interarrival_time_distribution=uniform_distribution)

simulate_service_station(num_shifts=3,
                         service_time_distribution=uniform_distribution,
                         interarrival_time_distribution=uniform_distribution)

simulate_service_station(num_shifts=10,
                         service_time_distribution=uniform_distribution,
                         interarrival_time_distribution=uniform_distribution)

print()
###

print('Комбинация гауссовского и равномерного распределений')
simulate_service_station(num_shifts=1,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=uniform_distribution)

simulate_service_station(num_shifts=3,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=uniform_distribution)

simulate_service_station(num_shifts=10,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=uniform_distribution)
print()

print("Гауссовское распределение с матожиданием 5 и СКО 2")
mu = 5
sigma = 2
simulate_service_station(num_shifts=1,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))

simulate_service_station(num_shifts=3,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))

simulate_service_station(num_shifts=10,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))
print()

print("Гауссовское распределение с матожиданием 8 и СКО 2")
mu = 8
sigma = 2
simulate_service_station(num_shifts=1,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))

simulate_service_station(num_shifts=3,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))

simulate_service_station(num_shifts=10,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))
print()

print("Гауссовское распределение с матожиданием 8 и СКО 9")
mu = 8
sigma = 9
simulate_service_station(num_shifts=1,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))

simulate_service_station(num_shifts=3,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))

simulate_service_station(num_shifts=10,
                         service_time_distribution=lambda: gauss_distribution(mu, sigma),
                         interarrival_time_distribution=lambda: gauss_distribution(mu, sigma))
print()