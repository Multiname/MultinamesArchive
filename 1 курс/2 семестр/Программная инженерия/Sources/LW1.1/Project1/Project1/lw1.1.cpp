#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

enum MenuCodes
{
	PRINT_ARRAY,
	TASK_1,
	TASK_2,
	TASK_3,
	EXIT
};

const int MINIMUM_RANDOM_NUMBER = -12;
const int MAXIMUM_RANDOM_NUMBER = 12;
const int MINIMUM_ARRAY_BORDER = 3;
const int MAXIMUM_ARRAY_BORDER = 17;

void Menu();
void FillArray(int** array, int arrayBorder, int mode);
void PrintArray(int** array, int arrayBorder);
int SumOfDigits(int number);
int FindSideDiagonalSameRowNumber(int** array, int lengthOfRow, int numberOfRow);
void IncreaseArrayElements(int** array, int arrayBorder);
void CheckSignAlternation(int** array, int arrayBorder);
void FindZeroElement(int** array, int arrayBorder);

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	Menu();

	return 0;
}

void Menu()
{
	cout << "������� ������ ���������� ������� (" << MINIMUM_ARRAY_BORDER << '-' << MAXIMUM_ARRAY_BORDER << "): ";
	int arrayBorder{};
	cin >> arrayBorder;

	while (arrayBorder < MINIMUM_ARRAY_BORDER || arrayBorder > MAXIMUM_ARRAY_BORDER)
	{
		cout << "������������ ��������, ���������� ��� ���: ";
		cin >> arrayBorder;
	}

	cout << "\n�������� ������ ������� �������\n";
	cout << "0. �������\n";
	cout << "1. ��������\n";
	cout << "�������� ������� : ";
	int mode{};
	cin >> mode;

	while (mode != 0 && mode != 1)
	{
		cout << "�������� �������, ���������� ��� ���: ";
		cin >> mode;
	}
	cout << '\n';

	int** array = new int* [arrayBorder] {};
	FillArray(array, arrayBorder, mode);

	int code = -1;
	while (code != EXIT)
	{
		cout << PRINT_ARRAY << ". ������� �������\n";
		cout << TASK_1 << ". ������� �������� � ������ ���� �������� �������� ��������� ��� �� ������\n";
		cout << TASK_2 << ". �������� ������ �� ����������� ������\n";
		cout << TASK_3 << ". ����� ������� �������� ��������\n";
		cout << EXIT << ". �����\n";
		cout << "�������� �������: ";
		cin >> code;
		while (code < PRINT_ARRAY || code > EXIT)
		{
			cout << "�������� �������, ���������� ��� ���: ";
			cin >> code;
		}
		cout << "\n";

		switch (code)
		{
		case PRINT_ARRAY:
			PrintArray(array, arrayBorder);
			break;
		case TASK_1:
			IncreaseArrayElements(array, arrayBorder);
			break;
		case TASK_2:
			CheckSignAlternation(array, arrayBorder);
			break;
		case TASK_3:
			FindZeroElement(array, arrayBorder);
			break;
		}
	}
}

void FillArray(int** array, int arrayBorder, int mode)
{
	if (mode == 0)
	{
		cout << "������� �������\n";
	}

	for (int i = 0; i < arrayBorder; i++)
	{
		array[i] = new int[arrayBorder] {};
		for (int j = 0; j < arrayBorder; j++)
		{
			if (mode == 0)
			{
				cin >> array[i][j];
			}
			else
			{
				array[i][j] = rand() % (MAXIMUM_RANDOM_NUMBER - MINIMUM_RANDOM_NUMBER + 1) + MINIMUM_RANDOM_NUMBER;
			}
		}
	}

	if (mode == 0)
	{
		cout << "\n";
	}
}

void PrintArray(int** array, int arrayBorder)
{
	cout << "    ";
	for (int columnNumber = 0; columnNumber < arrayBorder; columnNumber++)
	{
		cout << setw(4) << columnNumber;
	}
	cout << "\n\n";
	
	for (int row = 0; row < arrayBorder; row++)
	{
		cout << setw(2) << row << "  ";
		for (int column = 0; column < arrayBorder; column++)
		{
			cout << setw(4) << array[row][column];
		}
		cout << '\n';
	}
	cout << "\n";
}

int SumOfDigits(int number)
{
	if (abs(number) < 10)
	{
		return abs(number);
	}
	else
	{
		return abs(number) % 10 + abs(number / 10);
	}
}

int FindSideDiagonalSameRowNumber(int** array, int lengthOfRow, int numberOfRow)
{
	return array[numberOfRow][lengthOfRow - numberOfRow - 1];
}

void IncreaseArrayElements(int** array, int arrayBorder)
{
	for (int row = 0; row < arrayBorder; row++)
	{
		for (int column = 0; column < arrayBorder; column++)
		{
			if (column != arrayBorder - row - 1)
			{
				array[row][column] += SumOfDigits(FindSideDiagonalSameRowNumber(array, arrayBorder, row));
			}
		}

		array[row][arrayBorder - row - 1] += SumOfDigits(array[row][arrayBorder - row - 1]);
	}
}

void CheckSignAlternation(int** array, int arrayBorder) 
{

	int row{};
	cout << "������� ����� ������: ";
	cin >> row;

	if (row < 0 || row >= arrayBorder)
	{
		cout << "���� �������������� ������\n";
		return;
	}

	bool plusIsFound = false;
	bool minusIsFound = false;

	for (int column = 0; column < arrayBorder; column++)
	{
		if (array[row][column] > 0)
		{
			plusIsFound = true;
		}
		else if(array[row][column] < 0)
		{
			minusIsFound = true;
		}

	}

	if (plusIsFound && minusIsFound)
	{
		cout << "��������� ����������� ������\n";
	}
	else 
	{
		cout << "����������� ������ �� ���������\n";
	}
	cout << "\n";
}

void FindZeroElement(int** array, int arrayBorder)
{
	int foundRow = -1;
	int foundColumn = -1;
	int firstRowOfSearch = arrayBorder / 3;
	cout << "������ ������� ������: " << firstRowOfSearch << '\n';

	for (int row = firstRowOfSearch; row < arrayBorder; row++)
	{
		for (int column = 0; column < arrayBorder; column++)
		{
			if (array[row][column] == 0)
			{
				foundRow = row;
				foundColumn = column;
				break;
			}
		}
		if (foundRow != -1)
		{
			break;
		}
	}

	if (foundRow != -1)
	{
		cout << "������ ������� ������� ��������� � " << foundRow << " ������ " << foundColumn << " �������\n";
	}
	else
	{
		cout << "������� ��������� � ������� ������ ���\n";
	}
	cout << "\n";
}