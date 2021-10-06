#define _USE_MATH_DEFINES
#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	cout << "¬ведите целое число n от 1 до 5\n";
	cin >> n;


	float L;

	switch(n)
	{
		case(1):
			cout << "ƒеление на ноль\n";
			break;

		case(3):
			L = sqrt( pow((float)n, 2) / ((float)n - 1));
			cout << "L =  " << L;
			break;

		case(2):
			L = tan((float)n - 2);
			cout << "L =  " << L;
			break;

		case(4):
			L = atan(((float)n - 1) / ((float)n + 1));
			cout << "L =  " << L;
			break;

		case(5):
			L = sin((float)n / 2) + pow(M_E, (float)n);
			cout << "L =  " << L;
			break;
	}

}