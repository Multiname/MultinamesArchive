#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	int N = 0;
	cout << "������� ����������� �����: ";
	cin >> N;

	int k = 0;
	cout << "������� ���������� ������� ����: ";
	cin >> k;

	int sum = 0;

	for (int i = 0; i < k; i++)
	{
		sum += N % 10;
		N = N / 10;
	}

	cout << "����� " << k << " ������� ����: " << sum << endl;
}