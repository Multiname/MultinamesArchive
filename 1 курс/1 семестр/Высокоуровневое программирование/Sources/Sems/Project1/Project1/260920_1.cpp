#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	int k = 0;

	cout << "������� 5 ����� \n";

	int mas[5];

	for (int i = 0; i < 5; i++)
	{
		cin >> mas[i];
	}

	for (int i = 0; i < n; i++)
	{
		cout << "������� �����\n";
		int a = 0;
		cin >> a;

		if (a / 1000 > 0 && a / 1000 < 10)
		{
			int sum = a % 10 + (a / 10) % 10 +
				(a / 100) % 10 + a / 1000;

			if (sum == 15)
			{
				k += 1;
				
			}
		}
	}

	cout << "���������� ���������� �����: " << k << "\n";
}