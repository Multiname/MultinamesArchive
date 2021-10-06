#include <iostream>
#include "FindPlusOnSideDiagonal.h"

void FindPlusOnSideDiagonal(int** matrix, int rows, int columns)
{
	setlocale(LC_ALL, "Russian");
	int countPlus{};

	for (int i = 0; i < rows && i < columns; i++)
	{
		if (matrix[i][columns - i - 1] > 0)
		{
			countPlus++;
		}
	}
	std::cout << "���������� ������������� ����� �� �������� ���������: " << countPlus;
	std::cout << std::endl;
}