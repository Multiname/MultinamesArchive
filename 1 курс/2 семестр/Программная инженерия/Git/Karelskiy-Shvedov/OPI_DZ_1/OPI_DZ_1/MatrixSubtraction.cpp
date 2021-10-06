#include "MatrixSubtraction.h"
#include <iostream>

int** MatrixSubtraction(int** reducedMatrix, int** subtractableMatrix, int row, int column)
{
	int** differenceMatrix=new int*[row];
	for (short i = 0; i < row; ++i)
	{
		differenceMatrix[i] = new int[column];
	}

	for(short i{};i<row;++i)
	{
		for (short j{}; j < column; ++j)
		{
			differenceMatrix[i][j] = reducedMatrix[i][j] - subtractableMatrix[i][j];
		}
	}

	return differenceMatrix;
}