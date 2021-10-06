#include <iostream>
using namespace std;

const int MAXLEN = 255;

void filling(int Digits[], int border);
void piercing(int Digits[], int border);

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите натуральное число N>1: ";
	int N{};
	cin >> N;

	int Digits[MAXLEN]{};
	filling(Digits, N);
	piercing(Digits, N);

	cout << "Простые числа до N: " << endl;
	for (int i = 0; i < N; i++)
	{
		if (Digits[i] != 0)
		{
			cout << Digits[i] << " ";
		}
	}
	cout << endl;
}

void filling(int Digits[], int border)
{
	for (int d = 2; d < border; d++)
	{
		Digits[d - 2] = d;
	}
}

void piercing(int Digits[], int border)
{
	int curnum = 2;
	int num4check = 3;
	while (curnum < border)
	{
		for (int n4c = num4check; n4c < border; n4c++)
		{
			if (n4c % curnum == 0 && Digits[n4c - 2] != 0)
			{
				Digits[n4c - 2] = 0;
			}
		}
		curnum++;
		num4check++;
		while (Digits[curnum - 2] == 0 && curnum < border)
		{
			curnum++;
			num4check++;
		}
	}
}