#include "HashTable.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <chrono>

int main()
{
	//LITA_LW_5::HashTable table(5);
	//table.Print();
	//table.Add(5, "Bob");
	//table.Print();
	//table.Add(10, "Mike");
	//table.Print();
	//table.Add(11, "Alice");
	//table.Print();
	//std::string data = "";
	//table.Find(11, data);
	//std::cout << data << "\n";
	//std::cout << table.Find(15, data) << "\n";

	srand(time(NULL));
	size_t elementsNumber = 15;
	size_t tableSize = 20;
	std::vector<float>* addTimes = new std::vector<float>[elementsNumber]{};
	std::vector<float>* findTimes = new std::vector<float>[elementsNumber]{};
	std::vector<float> resultAddTimes{};
	std::vector<float> resultFindTimes{};
	for (int f{}; f < 5; ++f)
	{
		LITA_LW_5::HashTable hashTable(tableSize);

		std::vector<int> keys{};
		keys.push_back(rand() % tableSize);
		for (int j{}; j < elementsNumber - 1; ++j)
			keys.push_back(keys[j] + rand() % tableSize);

		std::vector<int> existingKeys{};
		for (int j{}; j < rand() % (elementsNumber + 1); ++j)
			existingKeys.push_back(keys[j]);
		for (int j = existingKeys.size(); j < elementsNumber; ++j)
			if (j == 0)
				existingKeys.push_back(rand() % tableSize);
			else
				existingKeys.push_back(existingKeys[j - 1] + rand() % tableSize);

		for (int j{}; j < elementsNumber; ++j)
		{
			std::string temp{};
			auto begin = std::chrono::steady_clock::now();
			hashTable.Find(existingKeys[j], temp);
			auto end = std::chrono::steady_clock::now();
			findTimes[j].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count());

			begin = std::chrono::steady_clock::now();
			hashTable.Add(keys[j], "Data");
			end = std::chrono::steady_clock::now();
			addTimes[j].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count());
		}
	}

	for (int i{}; i < elementsNumber; ++i)
	{
		float max = 0;
		float sum = 0;
		for (int j{}; j < 5; ++j)
		{
			sum += addTimes[i][j];
			if (addTimes[i][j] > max)
				max = addTimes[i][j];
		}
		resultAddTimes.push_back((sum - max) / 4);

		max = 0;
		sum = 0;
		for (int j{}; j < 5; ++j)
		{
			sum += findTimes[i][j];
			if (findTimes[i][j] > max)
				max = findTimes[i][j];
		}
		resultFindTimes.push_back((sum - max) / 4);
	}
		
	for (int i{}; i < elementsNumber; ++i)
	{
		std::cout << std::setw(6) << (float)i / tableSize << " " 
			<< std::setw(6) << resultAddTimes[i] << " " 
			<< std::setw(6) << resultFindTimes[i] << "\n";
	}

	return 0;
}