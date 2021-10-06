#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;
const int I = 9;
const int J = 10;
const int K = 8;
double f(double x, double y);
double p(int i, double z);
double h(int i, double z);

//новые прототипы
void rnd(double* arr, int len);
void out(double* arr, int len);
void change(double* arr, int len, double dvd);

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	double s;
	cout << "¬ведите s > 0: ";
	cin >> s;
	double t;
	cout << "¬ведите t > 0: ";
	cin >> t;
	double a = f(s + pow(t, 2), t) + f(s, t);
	double b = f(s + 5, t + 5) / t + s + f(s, t);
	double z;
	cout << "¬ведите z > 0: ";
	cin >> z;
	double c = pow(p(4, z), 2) / h(4, z);
	cout << endl;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl;

	double* n = new double[I] {};
	double* m = new double[J] {};
	double* l = new double[K] {};
	cout << "ƒо пребразований: " << endl;
	cout << "n: ";

	//использу€ новые функции
	rnd(n, I);
	out(n, I);

	/*
	for (int i = 0; i < I; i++)
	{
		n[i] = rand() % 1001 - 501;
		cout << setw(8) << n[i];
		if (n[i] > 0)
		{
			n[i] = n[i] / a;
		}
	}
	cout << endl;
	*/

	cout << "m: ";

	//использу€ новые функции
	rnd(m, J);
	out(m, J);

	/*
	for (int j = 0; j < J; j++)
	{
		m[j] = rand() % 1001 - 501;
		cout << setw(8) << m[j];
		if (m[j] > 0)
		{
			m[j] = m[j] / b;
		}
	}
	cout << endl;
	*/

	cout << "l: ";

	//использу€ новые функции
	rnd(l, K);
	out(l, K);

	/*
	for (int k = 0; k < K; k++)
	{
		l[k] = rand() % 1001 - 501;
		cout << setw(8) << l[k];
		if (l[k] > 0)
		{
			l[k] = l[k] / c;
		}
	}
	cout << endl;
	*/

	cout << "ѕосле пребразований: " << endl;
	cout << "n: ";

	//использу€ новые функции
	change(n, I, a);
	out(n, I);

	/*
	for (int i = 0; i < I; i++)
	{
		cout << setw(11) << n[i];
	}
	cout << endl;
	*/

	cout << "m: ";

	//использу€ новые функции
	change(m, J, b);
	out(m, J);

	/*
	for (int j = 0; j < J; j++)
	{
		cout << setw(11) << m[j];
	}
	cout << endl;
	*/

	cout << "l: ";

	//использу€ новые функции
	change(l, K, c);
	out(l, K);

	/*
	for (int k = 0; k < K; k++)
	{
		cout << setw(11) << l[k];
	}
	cout << endl;
	*/

	delete[] n;
	delete[] m;
	delete[] l;
}

double f(double x, double y)
{
	return sqrt(x * y) / sqrt(pow(x, 2) + 2 * x * y + y);
}

double p(int i, double z)
{
	if (i == 1)
	{
		return sqrt(z);
	}
	else
	{
		return p(i - 1, z) + 2 * p(i - 1, z) / z;
	}
}

double h(int i, double z)
{
	if (i == 1)
	{
		return cos(2);
	}
	else
	{
		return h(i - 1, z) + pow(h(i - 1, z), 2) / z;
	}
}

//новые функциии

void rnd(double* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = rand() % 1001 - 501;
	}
}

void out(double* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << setw(8) << arr[i];
	}
	cout << endl;
}

void change(double* arr, int len, double dvd)
{
	for (int i = 0; i < len; i++)
	{
		if (arr[i] < 0)
		{
			arr[i] = arr[i] / dvd;
		}
	}
}