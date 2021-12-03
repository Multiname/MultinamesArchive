#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
using namespace std;

extern "C" double calc(double);
extern "C" double compare(double);

int main() {
	double a, x;

	cout << "x = ";
	cin >> x;

	cout << endl << "Task 1" << endl;
	if (x > 1 && sin(x) != -M_PI / 6 && sin(x * x) > 0 && cos(log2(sqrt(sin(x * x)))) != 0)
	{
		a = (2 * log2(sqrt(pow(x, 4) - 1))) / (M_PI / (sin(x) + M_PI / 6)) - pow(tan(log2(sqrt(sin(x * x)))), 2);
		cout << "(C++) a = " << setprecision(15) << a << endl;

		a = calc(x);
		cout << "(Asm) a = " << setprecision(15) << a << endl;
	}
	else
	{
		cout << "Invalid x" << endl;
	}

	cout << endl << "Task 2" << endl;
	if (x < 1.1)
	{
		a = sin(x) + cos(x);
	}
	else if (x <= 5.1)
	{
		a = pow(2, x) - 1;
	}
	else
	{
		a = 9*x*x + 9;
	}
	cout << "(C++) f(x) = " << setprecision(15) << a << endl;

	a = compare(x);
	cout << "(Asm) f(x) = " << setprecision(15) << a << endl;

	return 0;
}