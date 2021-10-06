#include <iostream>
using namespace std;


const int ARRLEN = 26;
void main()
{
	setlocale(LC_ALL, "Russian");

	int S[ARRLEN]{};
	cout << "¬ведите 26 целых чисел: " << endl;
	for (int i = 0; i < ARRLEN; i++)
	{
		cin >> S[i];
	}
	cout << endl;

	int A[2][26]{};
	int NumOfEven = 0;
	int NumOfUneven = 0;
	for (int j = 0; j < ARRLEN; j++)
	{
		if (S[j] % 2 == 0)
		{
			A[0][NumOfEven] = S[j];
			NumOfEven++;
		}
		else
		{
			A[1][NumOfUneven] = S[j];
			NumOfUneven++;
		}
	}

	for (int n = 0; n < NumOfEven; n++)
	{
		cout << A[0][n] << " ";
	}
	cout << endl;
	for (int m = 0; m < NumOfUneven; m++)
	{
		cout << A[1][m] << " ";
	}
	cout << endl;
}