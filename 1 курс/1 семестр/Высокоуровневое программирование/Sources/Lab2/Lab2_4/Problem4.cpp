#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "¬ведите a\n";
	float a;
	cin >> a;

	if (a <= 1)
	{
		cout << "y = 1";
	}
	else if (a >= 1 and a <= 2)
	{
		cout << "y(a) =  "
			 << a * a;
	}
	else
	{
		cout << "y(a) = 4";
	}
}