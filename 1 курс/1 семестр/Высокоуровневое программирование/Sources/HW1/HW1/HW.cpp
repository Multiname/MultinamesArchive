#include <iostream>
#include <iomanip>
using namespace std;

const int ARRLEN = 6;
void main()
{
	setlocale(LC_ALL, "Russian");

	float A[ARRLEN][ARRLEN]{};
	for (int i1 = 0; i1 < ARRLEN; i1++)
	{
		for (int j1 = 0; j1 < ARRLEN; j1++)
		{
			A[i1][j1] = sqrt(i1 + 1) + (j1 + 1) / sin(i1 + 1);
		}
	}

	float B[ARRLEN][ARRLEN]{};
	float max = A[0][0];
	int j_max = 0;
	float min = A[0][0];
	int j_min = 0;
	for (int i2 = 0; i2 < ARRLEN; i2++)
	{
		for (int j2 = 0; j2 < ARRLEN; j2++)
		{
			if (A[i2][j2] < min)
			{
				min = A[i2][j2];
				j_min = j2;
			}
			if (A[i2][j2] > max)
			{
				max = A[i2][j2];
				j_max = j2;
			}
		}
	}
	for (int i3 = 0; i3 < ARRLEN; i3++)
	{
		for (int j3 = 0; j3 < ARRLEN; j3++)
		{
			if (j3 == j_min)
			{
				B[i3][j3] = A[i3][j_max];
			}
			else if (j3 == j_max)
			{
				B[i3][j3] = A[i3][j_min];
			}
			else
			{
				B[i3][j3] = A[i3][j3];
			}
		}
	}

	int C[ARRLEN][ARRLEN]{};
	for (int i4 = 0; i4 < ARRLEN; i4++)
	{
		for (int j4 = 0; j4 < ARRLEN; j4++)
		{
			if (i4 + j4 > 4)
			{
				C[i4][j4] = i4 + j4 - 4;
			}
		}
	}

	float D[ARRLEN][ARRLEN]{};
	for (int i5 = 0; i5 < ARRLEN; i5++)
	{
		for (int j5 = 0; j5 < ARRLEN; j5++)
		{
			for (int t = 0; t < ARRLEN; t++)
			{
				D[i5][j5] += B[i5][t] * C[t][j5];
			}
		}
	}

	float E[ARRLEN][ARRLEN]{};
	for (int i6 = 0; i6 < ARRLEN; i6++)
	{
		for (int j6 = 0; j6 < ARRLEN; j6++)
		{
			if ((i6 == 2 || i6 == 3) && (j6 == 4 || j6 == 5))
			{
				E[i6][j6] = D[i6 + 2][j6 - 2];
			}
			else if ((i6 == 4 || i6 == 5) && 
				(j6 == 2 || j6 == 3))
			{
				E[i6][j6] = D[i6 - 2][j6 + 2];
			}
			else
			{
				E[i6][j6] = D[i6][j6];
			}
		}
	}

	int min2 = E[0][0];
	int j_min2 = 0;
	for (int i7 = 0; i7 < ARRLEN; i7++)
	{
		for (int j7 = 0; j7 < ARRLEN; j7++)
		{
			if (E[i7][j7] < min2)
			{
				min2 = E[i7][j7];
				j_min2 = j7;
			}
		}
	}


	cout << "A: " << endl;
	for (int a1 = 0; a1 < ARRLEN; a1++)
	{
		for (int b1 = 0; b1 < ARRLEN; b1++)
		{
			cout << setw(7) << setprecision(3) <<  A[a1][b1];
		}
		cout << endl;
	}
	cout << endl;

	cout << "B: " << endl;
	for (int a2 = 0; a2 < ARRLEN; a2++)
	{
		for (int b2 = 0; b2 < ARRLEN; b2++)
		{
			cout << setw(7) << setprecision(3) << B[a2][b2];
		}
		cout << endl;
	}
	cout << endl;

	cout << "C: " << endl;
	for (int a3 = 0; a3 < ARRLEN; a3++)
	{
		for (int b3 = 0; b3 < ARRLEN; b3++)
		{
			cout << setw(2) << C[a3][b3];
		}
		cout << endl;
	}
	cout << endl;

	cout << "D: " << endl;
	for (int a4 = 0; a4 < ARRLEN; a4++)
	{
		for (int b4 = 0; b4 < ARRLEN; b4++)
		{
			cout << setw(8) << setprecision(4) << D[a4][b4];
		}
		cout << endl;
	}
	cout << endl;

	cout << "E: " << endl;
	for (int a5 = 0; a5 < ARRLEN; a5++)
	{
		for (int b5 = 0; b5 < ARRLEN; b5++)
		{
			cout << setw(8) << setprecision(4) << E[a5][b5];
		}
		cout << endl;
	}
	cout << endl;

	cout << "Номер столбца с минимальным элементом матрицы Е: "
		<< j_min + 1 << endl;
}