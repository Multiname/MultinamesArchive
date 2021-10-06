#include "ShuffleMatrix.h"

void ShuffleMatrix(int** matrix, int dimension)
{
	if (dimension % 3 == 0)
	{
		int blockDimension = dimension / 3;
		for (short i = 2 * blockDimension; i < dimension; i++)
		{
			for (short j = 0; j < blockDimension; j++)
			{
				int temp = matrix[i][j];
				matrix[i][j] = matrix[i - 2 * blockDimension][j + 2 * blockDimension];
				matrix[i - 2 * blockDimension][j + 2 * blockDimension] = temp;
			}
		}
	}
}