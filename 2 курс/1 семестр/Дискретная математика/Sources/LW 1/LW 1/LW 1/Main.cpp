#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	string A{};
	string B{};

	ifstream fileRead("data.txt");
	fileRead >> A;
	fileRead >> B;
	fileRead.close();

	cout << "Множество   Бинарный массив              Мощность   Буквы                     \n";
	
	size_t powerOfA = 0;
	string lettersOfA{};
	for (size_t i{}; i < A.length(); ++i)
	{
		if (A[i] == '1')
		{
			++powerOfA;
			lettersOfA.push_back(65 + i);
		}
	}
	cout << "A           " << A << "   " << powerOfA << "         ";
	if (powerOfA < 10)
	{
		cout << " ";
	}
	cout << lettersOfA << "\n";

	size_t powerOfB = 0;
	string lettersOfB{};
	for (size_t i{}; i < B.length(); ++i)
	{
		if (B[i] == '1')
		{
			++powerOfB;
			lettersOfB.push_back(65 + i);
		}
	}
	cout << "B           " << B << "   " << powerOfB << "         ";
	if (powerOfB < 10)
	{
		cout << " ";
	}
	cout << lettersOfB << "\n";

	size_t powerOfAAndB = 0;
	string letterOfAAndB{};
	cout << "A & B       ";
	for (size_t i{}; i < A.length(); ++i)
	{
		if (A[i] == '1' && B[i] == '1')
		{
			++powerOfAAndB;
			letterOfAAndB.push_back(65 + i);
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << "   " << powerOfAAndB << "         ";
	if (powerOfAAndB < 10)
	{
		cout << " ";
	}
	cout << letterOfAAndB << "\n";

	size_t powerOfAOrB = 0;
	string letterOfAOrB{};
	cout << "A U B       ";
	for (size_t i{}; i < A.length(); ++i)
	{
		if (A[i] == '1' || B[i] == '1')
		{
			++powerOfAOrB;
			letterOfAOrB.push_back(65 + i);
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << "   " << powerOfAOrB << "         ";
	if (powerOfAOrB < 10)
	{
		cout << " ";
	}
	cout << letterOfAOrB << "\n";

	size_t powerOfAMinusB = 0;
	string letterOfAMinusB{};
	cout << "A \\ B       ";
	for (size_t i{}; i < A.length(); ++i)
	{
		if (A[i] == '1' && B[i] == '0')
		{
			++powerOfAMinusB;
			letterOfAMinusB.push_back(65 + i);
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << "   " << powerOfAMinusB << "         ";
	if (powerOfAMinusB < 10)
	{
		cout << " ";
	}
	cout << letterOfAMinusB << "\n";

	size_t powerOfBMinusA = 0;
	string letterOfBMinusA{};
	cout << "B \\ A       ";
	for (size_t i{}; i < A.length(); ++i)
	{
		if (A[i] == '0' && B[i] == '1')
		{
			++powerOfBMinusA;
			letterOfBMinusA.push_back(65 + i);
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << "   " << powerOfBMinusA << "         ";
	if (powerOfBMinusA < 10)
	{
		cout << " ";
	}
	cout << letterOfBMinusA << "\n";

	size_t powerOfADeltaB = 0;
	string letterOfADeltaB{};
	cout << "B d A       ";
	for (size_t i{}; i < A.length(); ++i)
	{
		if (A[i] == '1' && B[i] == '0' || 
			A[i] == '0' && B[i] == '1')
		{
			++powerOfADeltaB;
			letterOfADeltaB.push_back(65 + i);
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << "   " << powerOfADeltaB << "         ";
	if (powerOfADeltaB < 10)
	{
		cout << " ";
	}
	cout << letterOfADeltaB << "\n";

	size_t powerOfNotA = 0;
	string letterOfNotA{};
	cout << "- A         ";
	for (size_t i{}; i < A.length(); ++i)
	{
		if (A[i] == '0')
		{
			++powerOfNotA;
			letterOfNotA.push_back(65 + i);
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << "   " << powerOfNotA << "         ";
	if (powerOfNotA < 10)
	{
		cout << " ";
	}
	cout << letterOfNotA << "\n";

	size_t powerOfNotB = 0;
	string letterOfNotB{};
	cout << "- B         ";
	for (size_t i{}; i < B.length(); ++i)
	{
		if (B[i] == '0')
		{
			++powerOfNotB;
			letterOfNotB.push_back(65 + i);
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << "   " << powerOfNotB << "         ";
	if (powerOfNotB < 10)
	{
		cout << " ";
	}
	cout << letterOfNotB << "\n";

	cout << "Контрольное значение: " << powerOfA + powerOfB +
		powerOfAAndB + powerOfAOrB + powerOfAMinusB + powerOfBMinusA +
		powerOfADeltaB + powerOfNotA + powerOfNotB << "\n";
}