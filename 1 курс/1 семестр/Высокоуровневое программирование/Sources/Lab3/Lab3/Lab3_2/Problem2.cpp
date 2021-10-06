#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	int N = 0;
	cout << "¬ведите натуральное число: ";
	cin >> N;

	int k = 0;
	cout << "¬ведите количество младших цифр: ";
	cin >> k;

	int sum = 0;

	for (int i = 0; i < k; i++)
	{
		sum += N % 10;
		N = N / 10;
	}

	cout << "—умма " << k << " младших цифр: " << sum << endl;
}