#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	int matrix[6][6]{};
	bool reflexiveMatrix[6][6]{};
	bool symmetricMatrix[6][6]{};
	bool transitiveMatrix1[6][6]{};
	int transitiveMatrix2[6][6]{};
	int temporaryMatrix[6][6]{};
	int cardinality = 0;

	ifstream fileRead("data.txt");
	for (uint16_t i{}; i < 6; ++i)
	{
		for (uint16_t j{}; j < 6; ++j)
		{
			string line{};
			fileRead >> line;

			matrix[i][j] = (int)line[0] - 48;
			reflexiveMatrix[i][j] = (int)line[0] - 48;
			symmetricMatrix[i][j] = (int)line[0] - 48;
			transitiveMatrix1[i][j] = (int)line[0] - 48;
			transitiveMatrix2[i][j] = (int)line[0] - 48;
			temporaryMatrix[i][j] = (int)line[0] - 48;

		}
	}
	fileRead.close();

	cout << "Исходное отношение:\n";
	for (uint16_t i{}; i < 6; ++i)
	{
		for (uint16_t j{}; j < 6; ++j)
		{
			cout << " " << (bool)matrix[i][j];
		}
		cout << "\n";
	}
	cout << "\n";

	reflexiveMatrix[0][0] = true;
	reflexiveMatrix[1][1] = true;
	reflexiveMatrix[2][2] = true;
	reflexiveMatrix[3][3] = true;
	reflexiveMatrix[4][4] = true;
	reflexiveMatrix[5][5] = true;

	cout << "Рефлексивное замыкание:\n";
	for (uint16_t i{}; i < 6; ++i)
	{
		for (uint16_t j{}; j < 6; ++j)
		{
			cout << " " << reflexiveMatrix[i][j];
		}
		cout << "\n";
	}
	cout << "\n";

	for (uint16_t i{}; i < 6; ++i)
	{
		for (uint16_t j{}; j < 6; ++j)
		{
			if (matrix[i][j])
			{
				symmetricMatrix[j][i] = true;
			}
		}
	}

	cout << "Симметричное замыкание:\n";
	for (uint16_t i{}; i < 6; ++i)
	{
		for (uint16_t j{}; j < 6; ++j)
		{
			cout << " " << symmetricMatrix[i][j];
		}
		cout << "\n";
	}
	cout << "\n";

	for (uint16_t k{}; k < 6; ++k)
	{
		for (uint16_t i{}; i < 6; ++i)
		{
			for (uint16_t j{}; j < 6; ++j)
			{
				if (transitiveMatrix1[i][k] && transitiveMatrix1[k][j])
				{
					transitiveMatrix1[i][j] = true;
				}
			}
		}
	}

	cout << "Транзитивное замыкание (1-й способ):\n";
	for (uint16_t i{}; i < 6; ++i)
	{
		for (uint16_t j{}; j < 6; ++j)
		{
			cout << " " << transitiveMatrix1[i][j];
		}
		cout << "\n";
	}
	cout << "\n";


	for (uint16_t k{}; k < 5; ++k)
	{
		int temp[6][6]{};

		for (uint16_t i{}; i < 6; ++i)
		{
			for (uint16_t j{}; j < 6; ++j)
			{
				temp[i][j] =
					temporaryMatrix[i][0] * matrix[0][j] +
					temporaryMatrix[i][1] * matrix[1][j] +
					temporaryMatrix[i][2] * matrix[2][j] +
					temporaryMatrix[i][3] * matrix[3][j] +
					temporaryMatrix[i][4] * matrix[4][j] +
					temporaryMatrix[i][5] * matrix[5][j];
			}
		}

		for (uint16_t i{}; i < 6; ++i)
		{
			for (uint16_t j{}; j < 6; ++j)
			{
				temporaryMatrix[i][j] = temp[i][j];
				transitiveMatrix2[i][j] += temp[i][j];
			}
		}
	}

	cout << "Транзитивное замыкание (2-й способ):\n";
	for (uint16_t i{}; i < 6; ++i)
	{
		for (uint16_t j{}; j < 6; ++j)
		{
			cout << " " << (bool)transitiveMatrix2[i][j];
		}
		cout << "\n";
	}
	cout << "\n";

	for (uint16_t i{}; i < 6; ++i)
	{
		for (uint16_t j{}; j < 6; ++j)
		{
			if (matrix[i][j])
			{
				++cardinality;
			}
			if (reflexiveMatrix[i][j])
			{
				++cardinality;
			}
			if (symmetricMatrix[i][j])
			{
				++cardinality;
			}
			if (transitiveMatrix1[i][j])
			{
				++cardinality;
			}
		}
	}

	cout << "Контрольное значение: " << cardinality << "\n";
}