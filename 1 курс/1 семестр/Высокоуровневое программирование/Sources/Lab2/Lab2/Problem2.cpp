#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "������� x\n";
	float x;
	cin >> x;

	cout << "������� y\n";
	float y;
	cin >> y;

	if (x >= -2 and x <= 1 and y <= 0 and y >= -1)
	{
		cout << "TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}
}