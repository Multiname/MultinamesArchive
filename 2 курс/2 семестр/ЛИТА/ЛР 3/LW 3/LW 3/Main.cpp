#include "PriorityQueue.h"
#include <random>
#include <time.h>
#include <chrono>
#include <fstream>

int main()
{
	//LITA::PriorityQueue<int> priorityQueue{};

	//priorityQueue.Enqueue(3, 3);
	//priorityQueue.Enqueue(4, 4);
	//priorityQueue.Enqueue(9, 9);
	//priorityQueue.Enqueue(5, 5);
	//priorityQueue.Enqueue(2, 2);

	//priorityQueue.PrintArray();

	//for (int i{}; i < 5; ++i)
	//	std::cout << priorityQueue.Dequeue() << " ";

	srand(time(NULL));

	std::vector<long long> times{};
	for (int i = 10; i <= 10; i += 100000)
	{
		LITA::PriorityQueue<int> priorityQueue{};

		int numberOfEnqueuing = 1 + rand() % (i - 1 + 1);
		std::vector<int> data{};
		for (int j{}; j < numberOfEnqueuing; ++j)
			data.push_back(1 + rand() % (9 - 1 + 1));

		int numberOfDequeuing = 0;
		if (numberOfEnqueuing != i)
			if (numberOfEnqueuing > i / 2)
				numberOfDequeuing = 0 + rand() % (i - numberOfEnqueuing - 0 + 1);
			else
				numberOfDequeuing = 0 + rand() % (numberOfEnqueuing - 0 + 1);

		int numberOfPeeking = 0 + rand() % (i - numberOfEnqueuing - numberOfDequeuing - 0 + 1);

		int numberOfIncreasing = i - numberOfEnqueuing - numberOfDequeuing - numberOfPeeking;
		std::vector<int> dataToIncrease{};
		std::vector<int> increases{};
		for (int j{}; j < numberOfIncreasing; ++j)
		{
			int d = data[0 + rand() % (data.size() - 1 - 0 + 1)];
			dataToIncrease.push_back(d);
			increases.push_back(d + 1 + rand() % (9 - 1 + 1));
		}

		clock_t workTime = 0;
		clock_t start{};
		clock_t end{};

		//long long workTime = 0;
		//std::chrono::steady_clock::time_point start{};
		//std::chrono::steady_clock::time_point end{};

		std::cout << "N = " << i << "\n";
		std::cout << "Enqueue:\n";
		for (int j{}; j < numberOfEnqueuing; ++j)
		{
			start = clock();
			priorityQueue.Enqueue(data[j], data[j]);
			end = clock();
			workTime += end - start;
			priorityQueue.PrintArray();
			std::cout << "\n";
		}
		std::cout << "Peek:\n";
		for (int j{}; j < numberOfPeeking; ++j)
		{
			int peek;
			start = clock();
			peek = priorityQueue.Peek();
			end = clock();
			workTime += end - start;
			std::cout << peek << "\n";
		}
		std::cout << "\nIncreasePriority:\n";
		for (int j{}; j < numberOfIncreasing; ++j)
		{
			start = clock();
			priorityQueue.IncreasePriority(dataToIncrease[j], increases[j]);
			end = clock();
			workTime += end - start;
			priorityQueue.PrintArray();
			std::cout << "\n";
		}
		std::cout << "Dequeue:\n";
		for (int j{}; j < numberOfDequeuing; ++j)
		{
			int dequeue;
			start = clock();
			dequeue = priorityQueue.Dequeue();
			end = clock();
			workTime += end - start;
			std::cout << dequeue << "\n";
		}

		std::cout << "\nTime: " << workTime / (CLOCKS_PER_SEC / 1000) << "\n";
		std::cout << "numberOfEnqueuing: " << numberOfEnqueuing << "\n";
		std::cout << "numberOfPeeking: " << numberOfPeeking << "\n";
		std::cout << "numberOfIncreasing: " << numberOfIncreasing << "\n";
		std::cout << "numberOfDequeuing: " << numberOfDequeuing << "\n";
		times.push_back(workTime / (CLOCKS_PER_SEC / 1000));
	}

	std::ofstream file("WorkTimes.csv");
	for (int i{}; i < times.size(); ++i)
	{
		//std::cout << times[i] << "\n";
		file << times[i] << '\n';
	}
	file.close();

	return 0;
}