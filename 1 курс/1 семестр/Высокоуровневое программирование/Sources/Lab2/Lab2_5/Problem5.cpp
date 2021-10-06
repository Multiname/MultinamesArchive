#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "¬ведите A\n";
	float A;
	cin >> A;

	cout << "¬ведите B\n";
	float B;
	cin >> B;

	cout << "¬ведите C\n";
	float C;
	cin >> C;



	if (B < A && A < C)
	{
		A *= 2;
		B *= 2;
		C *= 2;
	}
	else if (A < B && B < C)
	{
		C *= C;
	}
	else
	{
		if (A <= B && A <= C)
		{
			B = A;
			C = A;
		}
		else if (B <= A && B <= C)
		{
			A = B;
			C = B;
		}
		else
		{
			A = C;
			B = C;
		}
	}

	cout << "A = " << A << "\n"
		 << "B = " << B << "\n"
	 	 << "C = " << C << "\n";
}