#include <iostream>
#include "ReplaceMinusUnderMainDiagonal.h"

void ReplaceMinusUnderMainDiagonal(int** matrix, int rows, int columns)
{
	for (int i = 1; i < rows; i++)
	{
		for (int j = 0; j < i && j<columns; j++)
		{
			if (matrix[i][j] < 0)
			{
				matrix[i][j] = 0;
			}
	
		}
	}
}