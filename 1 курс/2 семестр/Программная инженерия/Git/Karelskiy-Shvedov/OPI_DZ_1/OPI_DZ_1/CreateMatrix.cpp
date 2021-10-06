#include "CreateMatrix.h"
#include <ctime>;
#include <iostream>

int** CreateMatrix(int rows, int columns,  bool mode, int minimalRandomNumber, int maximalRandomNumber)
{
	int** matrix = new int* [rows];

	if (mode == false)
	{
		srand(time(0));

		for (short i = 0; i < rows; i++)
		{
			matrix[i] = new int[columns];

			for (short j = 0; j < columns; j++)
			{
				matrix[i][j] = rand() % (maximalRandomNumber - minimalRandomNumber + 1) + minimalRandomNumber;
			}
		}
	}
	else
	{
		for (short i = 0; i < rows; i++)
		{
			matrix[i] = new int[columns];

			for (short j = 0; j < columns; j++)
			{
				std::cin >> matrix[i][j];
			}
		}
	}
	
	return matrix;
}