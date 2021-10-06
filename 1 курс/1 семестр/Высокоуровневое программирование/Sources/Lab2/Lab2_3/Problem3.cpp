#include <iostream>
#include <cmath>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите a\n";
	float a;
	cin >> a;
	if (a != -1)
	{
		int b = (17 * a * a * a) / pow(a + 1, 2);
		cout << "Количество сотен в целой части значения выражения: "
			<< (b % 1000) / 100;
	}
	else
	{
		cout << "Деление на ноль";
	}
}