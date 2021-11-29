#define _USE_MATH_DEFINES
#include <iostream>
using namespace std;

extern "C" double calc(double);

int main() {
	double a, x;

	cout << "x = ";
	cin >> x;

	a = (2 * log2(sqrt(pow(x, 4) - 1))) / (M_PI / (sin(x) + M_PI / 6)) - pow(tan(log2(sqrt(sin(x*x)))), 2);
	cout << "(C++) a = " << a << endl;

	a = calc(x);
	cout << "(Asm) a = " << a << endl;

	return 0;
}