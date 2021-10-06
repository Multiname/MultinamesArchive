#include <iostream>
#include <math.h>
using namespace std;
void main() 
{
	setlocale(LC_ALL, "Russian");

	cout << "¬ведите x\n";
	float x;
	cin >> x;

	cout << "¬ведите y\n";
	float y;
	cin >> y;

	cout << "¬ведите z\n";
	float z;
	cin >> z;



	float a;
	a = (1 + pow(sin(x + y), 2))/(2 + abs(x - (2*x)/(1 + x*x * y*y))) + z*z*z;

	float b;
	bool flag;
	if (x > 0 && x != 1 && cos(z) != 0)
	{
		b = pow(x + y, 2) / log(pow(x, 2 + 1)) - (pow(cos(x), 2) + tan(z));
		flag = true;
	}
	else
	{
		flag = false;
	}


	cout << "a = ";
	cout << a << "\n";

	if (flag == true)
	{
		cout << "b = ";
		cout << b << "\n";
	}
	else
	{
		cout << "b невозможно посчитать\n";
	}
}