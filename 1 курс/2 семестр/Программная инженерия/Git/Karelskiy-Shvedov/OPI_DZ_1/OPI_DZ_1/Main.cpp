#include "CreateMatrix.h"
#include "PrintMatrix.h"
#include "FindPlusOnSideDiagonal.h"
#include "ReplaceMinusUnderMainDiagonal.h"
#include <iostream>
#include "CalculateDeterminant.h"
#include "ShuffleMatrix.h"
#include "MatrixSubtraction.h"
#include "SortInAscendingOrder.h"

const int MAXIMUM_INPUT_LENGHT = 255;

int main()
{
	setlocale(LC_ALL, "Russian");

	char command[MAXIMUM_INPUT_LENGHT]{};

	int rows = 9;
	int columns = 9;

	std::cout << "������� 1, ���� ������ �������� ������ ������� (�� ��. 9�9): ";
	std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
	if (!strcmp(command, "1"))
	{
		std::cout << "������� ���-�� �����: ";
		std::cin >> rows;
		std::cout << "������� ���-�� ��������: ";
		std::cin >> columns;
		std::cin.ignore(32767, '\n');
	}

	int** matrix{};
	int cellWidth = 1;

	std::cout << "������� 1, ���� ������ ������ �������� ��������� ������� (�� ��. ��������� ����������): ";
	std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
	if (!strcmp(command, "1"))
	{
		std::cout << "������� ������� " << rows << "x" << columns << "\n";
		matrix = CreateMatrix(rows, columns, 1);
	}
	else
	{
		int minimalRandomNumber = 0;
		int maximalRandomNumber = 0;

		std::cout << "������� 1, ���� ������ �������� ������� ��������� ����� (�� ��. [-21; 23]): ";
		std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
		if (!strcmp(command, "1"))
		{
			std::cout << "������� ����������� ��������� �����: ";
			std::cin >> minimalRandomNumber;
			std::cout << "������� ������������ ��������� �����: ";
			std::cin >> maximalRandomNumber;
			std::cin.ignore(32767, '\n');
		}
		else
		{
			minimalRandomNumber = -21;
			maximalRandomNumber = 23;
		}

		if (minimalRandomNumber < 0)
		{
			cellWidth++;
		}
		int tens = 10;
		while (tens < abs(minimalRandomNumber) || tens < abs(maximalRandomNumber))
		{
			cellWidth++;
			tens *= 10;
		}

		matrix = CreateMatrix(rows, columns, 0, minimalRandomNumber, maximalRandomNumber);
	}

	std::cout << "��������� �������:\n\n";
	PrintMatrix(matrix, rows, columns, cellWidth);

	FindPlusOnSideDiagonal(matrix, rows, columns);
	std::cout << '\n';

	ReplaceMinusUnderMainDiagonal(matrix, rows, columns);
	std::cout << "������� ����� ������ ������������� �����, ����������� ���� ������� ���������, �� 0:\n\n";
	PrintMatrix(matrix, rows, columns, cellWidth);

	if (rows == columns)
	{
		std::cout << "������������ �������: " << CalculateDeterminant(matrix, rows) << "\n\n";

		if (rows % 3 == 0)
		{
			ShuffleMatrix(matrix, rows);
			std::cout << "������� ����� �����������:\n\n";
			PrintMatrix(matrix, rows, columns, cellWidth);
		}
		else
		{
			std::cout << "���������� ������������ ������� c �� ������� ���� ������������\n\n";
		}
	}
	else
	{
		std::cout << "���������� ��������� ������������ � ������������ ������������� �������\n\n";
	}

	int** matrix_2{};
	int cellWidth_2 = 1;

	std::cout << "������� 1, ���� ������ ������ �������� ��������� ������ ������� (�� ��. ��������� ����������): ";
	std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
	if (!strcmp(command, "1"))
	{
		std::cout << "������� ������� " << rows << "x" << columns << "\n";
		matrix_2 = CreateMatrix(rows, columns, 1);
	}
	else
	{
		int minimalRandomNumber = 0;
		int maximalRandomNumber = 0;

		std::cout << "������� 1, ���� ������ �������� ������� ��������� ����� (�� ��. [-21; 23]): ";
		std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
		if (!strcmp(command, "1"))
		{
			std::cout << "������� ����������� ��������� �����: ";
			std::cin >> minimalRandomNumber;
			std::cout << "������� ������������ ��������� �����: ";
			std::cin >> maximalRandomNumber;
			std::cin.ignore(32767, '\n');
		}
		else
		{
			minimalRandomNumber = -21;
			maximalRandomNumber = 23;
		}

		if (minimalRandomNumber < 0)
		{
			cellWidth_2++;
		}
		int tens = 10;
		while (tens < abs(minimalRandomNumber) || tens < abs(maximalRandomNumber))
		{
			cellWidth_2++;
			tens *= 10;
		}

		matrix_2 = CreateMatrix(rows, columns, 0, minimalRandomNumber, maximalRandomNumber);
	}

	std::cout << "������ ��������� �������:\n\n";
	PrintMatrix(matrix_2, rows, columns, cellWidth_2);

	matrix = MatrixSubtraction(matrix, matrix_2, rows, columns);
	std::cout << "������ ������� ����� ��������� �� ��� ������:\n\n";
	PrintMatrix(matrix, rows, columns, cellWidth);

	SortInAscendingOrder(matrix, rows, columns);
	std::cout << "������ ������� ����� ����������:\n\n";
	PrintMatrix(matrix, rows, columns, cellWidth);

	return 0;
}