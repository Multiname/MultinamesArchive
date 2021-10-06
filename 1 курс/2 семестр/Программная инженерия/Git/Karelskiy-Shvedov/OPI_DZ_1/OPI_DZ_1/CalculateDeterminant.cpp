#include "CalculateDeterminant.h"
#include <cmath>

int CalculateDeterminant(int** matrix, int dimension)
{
	if (dimension == 2)
	{
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else
	{
		int determinant = 0;
		int** submatrix = new int* [dimension - 1]{};
		for (short i = 0; i < dimension - 1; ++i)
		{
			submatrix[i] = new int[dimension - 1]{};
		}
		int row{};
		int column{};

		for (short i = 0; i < dimension; ++i)
		{
			row = 0;
			for (short j = 1; j < dimension; ++j)
			{
				column = 0;
				for (short k = 0; k < dimension; ++k)
				{
					if (k != i)
					{
						submatrix[row][column] = matrix[j][k];
						++column;
					}
				}
				++row;
			}
			determinant += pow(-1, i) * matrix[0][i] * CalculateDeterminant(submatrix, dimension - 1);
		}
		return determinant;
	}
}