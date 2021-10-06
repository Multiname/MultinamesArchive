#include <iostream>
using namespace std;

const int MAX_N = 15;
void main()
{
	setlocale(LC_ALL, "Russian");

	int M[MAX_N][MAX_N]{};
	cout << "Введите количество населенных пунктов N: ";
	int N{};
	cin >> N;
	cout << "Задайте сеть авиалиний: " << endl;
	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < N; m++)
		{
			cin >> M[n][m];
		}
	}
	cout << endl;

	bool IsolatedExist = false;
	for (int i = 0; i < N; i++)
	{
		bool Connected = false;

		for (int j = 0; j < N; j++)
		{
			if (M[i][j] == 1)
			{
				Connected = true;
			}
		}

		if (Connected == false)
		{
			IsolatedExist = true;
		}
	}

	if (IsolatedExist == true)
	{
		cout << "Есть изолированный город" << endl;
	}
	else
	{
		cout << "Нет изолированных городов" << endl;
	}
}