#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

void RunFirst()
{
	cout << "N: ";
	uint16_t N{};
	cin >> N;

	uint16_t minimum = UINT16_MAX;
	uint16_t maximum = 0;

	for (uint16_t i{}; i < N; ++i)
	{
		cout << i + 1 << ": ";
		uint16_t input{};
		cin >> input;

		if (input > maximum)
		{
			maximum = input;
		}

		if (input < minimum)
		{
			minimum = input;
		}
	}

	cout << "Max: " << maximum << "\n";
	cout << "Min: " << minimum << "\n";
	system("pause");
}

void RunSecond()
{
	cout << "N: ";
	uint16_t N{};
	cin >> N;

	uint16_t firstMaximum = 0;
	uint16_t secondMaximum = 0;

	for (uint16_t i{}; i < N; ++i)
	{
		cout << i + 1 << ": ";
		uint16_t input{};
		cin >> input;

		if (input > firstMaximum && input > secondMaximum)
		{
			secondMaximum = firstMaximum;
			firstMaximum = input;
		}
		else if (input > secondMaximum)
		{
			secondMaximum = input;
		}
	}

	cout << "First max: " << firstMaximum << "\n";
	cout << "Second max: " << secondMaximum << "\n";
	system("pause");
}

void RunThird()
{
	cout << "N: ";
	uint16_t N{};
	cin >> N;

	set<uint16_t> numbers{};
	for (uint16_t i{}; i < N; ++i)
	{
		cout << i + 1 << ": ";
		uint16_t input{};
		cin >> input;
		numbers.insert(input);
	}

	if (numbers.size() % 2 == 0)
	{
		float sum = 0;
		for (set<uint16_t>::iterator it = numbers.begin(); it != numbers.end(); ++it)
		{
			sum += *it;
		}
		cout << "Median: " << sum / numbers.size() << "\n";
	}
	else
	{
		int position = numbers.size() / 2;
		set<uint16_t>::iterator it = numbers.begin();
		advance(it, position);
		cout << "Median: " << *it << "\n";
	}
	system("pause");
}

void RunFourth()
{
	cout << "N: ";
	uint16_t N{};
	cin >> N;

	map<uint16_t, uint16_t> numbers{};

	for (uint16_t i{}; i < N; ++i)
	{
		cout << i + 1 << ": ";
		uint16_t input{};
		cin >> input;

		bool isFound = false;
		for (map<uint16_t, uint16_t>::iterator it = numbers.begin(); it != numbers.end(); ++it)
		{
			if (input == (*it).first)
			{
				isFound = true;
				break;
			}
		}

		if (isFound)
		{
			++numbers[input];
		}
		else
		{
			numbers.insert(make_pair(input, 1));
		}
	}

	uint16_t firstMaximumNumber = 0;
	uint16_t secondMaximumNumber = 0;
	uint16_t firstNumber{};

	for (map<uint16_t, uint16_t>::iterator it = numbers.begin(); it != numbers.end(); ++it)
	{
		if ((*it).second > firstMaximumNumber && (*it).second > secondMaximumNumber)
		{
			secondMaximumNumber = firstMaximumNumber;
			firstMaximumNumber = (*it).second;

			firstNumber = (*it).first;
		}
		else if ((*it).second > secondMaximumNumber)
		{
			secondMaximumNumber = (*it).second;
		}
	}

	if (firstMaximumNumber == secondMaximumNumber)
	{
		cout << "There is no mode\n";
	}
	else
	{
		cout << "Mode: " << firstNumber << "\n";
	}

	system("pause");
}

void RunFifth()
{
	cout << "N: ";
	uint16_t N{};
	cin >> N;

	if (N > 1)
	{
		for (uint16_t i = 2; i <= N / 2; ++i)
		{
			if (N % i == 0)
			{
				cout << "The number is not prime\n";
				system("pause");
				return;
			}
		}
	}

	cout << "The number is prime\n";
	system("pause");
}

void RunSixth()
{
	cout << "N: ";
	uint16_t N{};
	cin >> N;

	uint16_t divisior = 2;
	while (N != 1)
	{
		if (N % divisior == 0)
		{
			cout << divisior << " ";
			N = N / divisior;
		}
		else
		{
			++divisior;
		}
	}
	cout << "1\n";
	system("pause");
}

void main()
{
	setlocale(LC_ALL, "Russian");
	
	uint16_t task = 1;
	while (task)
	{
		cout << "Task (0 - exit): ";
		cin >> task;

		switch (task)
		{
		case 1:
			RunFirst();
			break;
		case 2:
			RunSecond();
			break;
		case 3:
			RunThird();
			break;
		case 4:
			RunFourth();
			break;
		case 5:
			RunFifth();
			break;
		case 6:
			RunSixth();
			break;
		}

		system("cls");
	}
}