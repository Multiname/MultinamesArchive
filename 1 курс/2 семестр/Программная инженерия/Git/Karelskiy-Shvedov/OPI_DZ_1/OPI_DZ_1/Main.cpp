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

	std::cout << "Введите 1, если хотите поменять размер матрицы (по ум. 9х9): ";
	std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
	if (!strcmp(command, "1"))
	{
		std::cout << "Введите кол-во строк: ";
		std::cin >> rows;
		std::cout << "Введите кол-во столбцов: ";
		std::cin >> columns;
		std::cin.ignore(32767, '\n');
	}

	int** matrix{};
	int cellWidth = 1;

	std::cout << "Введите 1, если хотите задать значения элементов матрицы (по ум. случайное заполнение): ";
	std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
	if (!strcmp(command, "1"))
	{
		std::cout << "Введите матрицу " << rows << "x" << columns << "\n";
		matrix = CreateMatrix(rows, columns, 1);
	}
	else
	{
		int minimalRandomNumber = 0;
		int maximalRandomNumber = 0;

		std::cout << "Введите 1, если хотите изменить границы случайных чисел (по ум. [-21; 23]): ";
		std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
		if (!strcmp(command, "1"))
		{
			std::cout << "Введите минимальное случайное число: ";
			std::cin >> minimalRandomNumber;
			std::cout << "Введите максимальное случайное число: ";
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

	std::cout << "Созданная матрица:\n\n";
	PrintMatrix(matrix, rows, columns, cellWidth);

	FindPlusOnSideDiagonal(matrix, rows, columns);
	std::cout << '\n';

	ReplaceMinusUnderMainDiagonal(matrix, rows, columns);
	std::cout << "Матрица после замены отрицательных чисел, находящихся ниже главной диагонали, на 0:\n\n";
	PrintMatrix(matrix, rows, columns, cellWidth);

	if (rows == columns)
	{
		std::cout << "Определитель матрицы: " << CalculateDeterminant(matrix, rows) << "\n\n";

		if (rows % 3 == 0)
		{
			ShuffleMatrix(matrix, rows);
			std::cout << "Матрица после перетасовки:\n\n";
			PrintMatrix(matrix, rows, columns, cellWidth);
		}
		else
		{
			std::cout << "Невозможно перетасовать матрицу c не кратной трем размерностью\n\n";
		}
	}
	else
	{
		std::cout << "Невозможно посчитать определитель и перетасовать прямоугольную матрицу\n\n";
	}

	int** matrix_2{};
	int cellWidth_2 = 1;

	std::cout << "Введите 1, если хотите задать значения элементов второй матрицы (по ум. случайное заполнение): ";
	std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
	if (!strcmp(command, "1"))
	{
		std::cout << "Введите матрицу " << rows << "x" << columns << "\n";
		matrix_2 = CreateMatrix(rows, columns, 1);
	}
	else
	{
		int minimalRandomNumber = 0;
		int maximalRandomNumber = 0;

		std::cout << "Введите 1, если хотите изменить границы случайных чисел (по ум. [-21; 23]): ";
		std::cin.getline(command, MAXIMUM_INPUT_LENGHT, '\n');
		if (!strcmp(command, "1"))
		{
			std::cout << "Введите минимальное случайное число: ";
			std::cin >> minimalRandomNumber;
			std::cout << "Введите максимальное случайное число: ";
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

	std::cout << "Вторая созданная матрица:\n\n";
	PrintMatrix(matrix_2, rows, columns, cellWidth_2);

	matrix = MatrixSubtraction(matrix, matrix_2, rows, columns);
	std::cout << "Первая матрица после вычитания из нее второй:\n\n";
	PrintMatrix(matrix, rows, columns, cellWidth);

	SortInAscendingOrder(matrix, rows, columns);
	std::cout << "Первая матрица после сортировки:\n\n";
	PrintMatrix(matrix, rows, columns, cellWidth);

	return 0;
}