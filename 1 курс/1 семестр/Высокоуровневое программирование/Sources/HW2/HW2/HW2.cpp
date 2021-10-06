#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

const int I = 11;
const int J = 10;
const int K = 9;

float f(float x, float y);
float p(int i, float z);
float h(int i, float z);
void tf(float& elem, float mult);

void main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	float s{};
	cout << "Введите s > 0: ";
	cin >> s;
	float t{};
	cout << "Введите t > 0: ";
	cin >> t;
	float a = f(pow(s, 3), t) + f(s, t);
	float b = f(t + 2, sqrt(s)) / f(s, t) + f(t, s + 2);
	float z{};
	cout << "Введите z > 0: ";
	cin >> z;
	float c = sqrt(abs(p(4, z) + h(6, z)));
	cout << endl;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl;

	float* n = new float[I] {};
	float* m = new float[J] {};
	float* l = new float[K] {};
	cout << "До пребразований" << endl;
	cout << "n: ";
	for (int i = 0; i < I; i++)
	{
		n[i] = rand() % (100 + 100 + 1) - 100;
		cout << setw(13) << n[i];
	}
	cout << endl;
	cout << "m: ";
	for (int j = 0; j < J; j++)
	{
		m[j] = rand() % (100 + 100 + 1) - 100;
		cout << setw(13) << m[j];
	}
	cout << endl;
	cout << "l: ";
	for (int k = 0; k < K; k++)
	{
		l[k] = rand() % (100 + 100 + 1) - 100;
		cout << setw(13) << l[k];
	}
	cout << endl;

	cout << "После пребразований" << endl;
	cout << "n: ";
	for (int i = 0; i < I; i++)
	{
		tf(n[i], a);
		cout << setw(13) << n[i];
	}
	cout << endl;
	cout << "m: ";
	for (int j = 0; j < J; j++)
	{
		tf(m[j], c);
		cout << setw(13) << m[j];
	}
	cout << endl;
	cout << "l: ";
	for (int k = 0; k < K; k++)
	{
		tf(l[k], 0);
		cout << setw(13) << l[k];
	}
	cout << endl;

	delete[] n;
	delete[] m;
	delete[] l;
}

float f(float x, float y)
{
	return (pow(y, 3) + sqrt(pow(x, 33))) / 8;
}

float p(int i, float z)
{
	if (i == 1)
	{
		return cos(2);
	}
	else
	{
		return p(i - 1, z) + z * p(i - 1, z);
	}
}

float h(int i, float z)
{
	if (i == 1)
	{
		return sin(2);
	}
	else
	{
		return h(i - 1, z) / (5 * z) + sqrt(h(i - 1, z));
	}
}

void tf(float &elem, float mult)
{
	if (elem < 0)
	{
		elem *= mult;
	}
}