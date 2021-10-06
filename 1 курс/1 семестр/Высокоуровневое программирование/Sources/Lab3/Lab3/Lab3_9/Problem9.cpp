#include <iostream>
#include <iomanip>
using namespace std;

const int MaxArrayLength = 19;
void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "¬ведите размер матрицы: ";
	int ArrayLength{};
	cin >> ArrayLength;
	cout << endl;
	int M[MaxArrayLength][MaxArrayLength]{};

	int FirstNum = 1;
	for (int i = 0; i < ArrayLength; i++)
	{
		int j = 0;
		for (int num = FirstNum; num > 0; num--)
		{
			M[i][j] = num;
			j++;
		}
		FirstNum++;
	}

	for (int n = 0; n < ArrayLength; n++)
	{
		for (int m = 0; m < ArrayLength; m++)
		{
			cout << setw(3) << M[n][m];
		}
		cout << endl;
	}
}