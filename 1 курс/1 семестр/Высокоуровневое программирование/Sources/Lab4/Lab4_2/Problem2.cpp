#include <iostream>
#include <iomanip>
using namespace std;

const int MAXLEN = 20;

void myswap(int& a, int& b);
int numlen(int num);
void sort(int sums[], int indexes[], int matrix_columns);

void main()
{
	setlocale(LC_ALL, "Russian");

	int matrix_lines{};
	cout << "¬ведите кол-во строк матрицы: ";
	cin >> matrix_lines;
	int matrix_columns{};
	cout << "¬ведите кол-во столбцов матрицы: ";
	cin >> matrix_columns;
	int maxlen = 1;
	int Matrix[MAXLEN][MAXLEN]{};
	cout << "¬ведите матрицу: " << endl;
	for (int i = 0; i < matrix_lines; i++)
	{
		for (int j = 0; j < matrix_columns; j++)
		{
			cin >> Matrix[i][j];
			int len = numlen(Matrix[i][j]);
			if (len > maxlen)
			{
				maxlen = len;
			}
		}
	}

	int sums[MAXLEN]{};
	int indexes[MAXLEN]{};

	for (int m = 0; m < matrix_columns; m++)
	{
		indexes[m] = m;
		for (int n = 0; n < matrix_lines; n++)
		{
			sums[m] += Matrix[n][m];
		}
	}

	sort(sums, indexes, matrix_columns);

	cout << "ќтсортированна€ матрица: " << endl;
	for (int a = 0; a < matrix_lines; a++)
	{
		int TempMatrix[MAXLEN]{};
		for (int b = 0; b < matrix_columns; b++)
		{
			TempMatrix[b] = Matrix[a][b];
		}
		for (int c = 0; c < matrix_columns; c++)
		{
			Matrix[a][c] = TempMatrix[indexes[c]];
			cout << setw(maxlen + 1) <<  Matrix[a][c];
		}
		cout << endl;
	}
}

void myswap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int numlen(int num)
{
	int len = 1;
	if (num < 0)
	{
		len++;
		num = abs(num);
	}
	while (num / 10 != 0)
	{
		num = num / 10;
		len++;
	}
	return len;
}

void sort(int sums[], int indexes[], int matrix_columns)
{
	bool check = true;
	int start = 0;
	int end = matrix_columns - 1;
	while (check)
	{
		check = false;
		for (int p = start; p < end; p++)
		{
			if (sums[p] < sums[p + 1])
			{
				check = true;
				myswap(sums[p], sums[p + 1]);
				myswap(indexes[p], indexes[p + 1]);
			}
		}
		start++;

		for (int q = end; q > start - 1; q--)
		{
			if (sums[q] > sums[q - 1])
			{
				check = true;
				myswap(sums[q], sums[q - 1]);
				myswap(indexes[q], indexes[q - 1]);
			}
		}
		end--;
	}
}