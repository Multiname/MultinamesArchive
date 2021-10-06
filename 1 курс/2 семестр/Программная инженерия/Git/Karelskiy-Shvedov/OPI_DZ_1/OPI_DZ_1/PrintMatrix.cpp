#include "PrintMatrix.h"
#include <iostream>
#include <iomanip>

void PrintMatrix(int** matrix, int rows, int columns, int cellWidth)
{
	short numberColumnWidth{};
	int tempRows = rows;
	while (tempRows != 0)
	{
		tempRows /= 10;
		numberColumnWidth++;
		std::cout << " ";
	}
	std::cout << "  ";

	for (short i = 0; i < columns; i++)
	{
		std::cout << std::setw(cellWidth) << i << " ";
	}
	std::cout << "\n\n\n";

	for (short i = 0; i < rows; i++)
	{
		std::cout << std::setw(numberColumnWidth) << i;
		std::cout << "  ";
		for (short j = 0; j < columns; j++)
		{
			std::cout << std::setw(cellWidth) << matrix[i][j] << " ";
		}
		std::cout << "\n\n";
	}
}