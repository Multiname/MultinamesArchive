#include <iostream>
#include <ctime>
using namespace std;

const int ARRLEN = 75;
const int BOT = -5;
const int UPP = 40;
void main()
{
	srand(time(0));
	int A[ARRLEN]{};
	int Y[ARRLEN]{};
	int j = 0;
	cout << "A: " << endl;
	for (int i = 0; i < ARRLEN; i++)
	{
		A[i] = rand() % (UPP - BOT + 1) + BOT;
		cout << A[i] << " ";
		if (A[i] < 20)
		{
			Y[j] = A[i];
			j++;
		}
	}
	cout << endl << endl;

	cout << "Y: " << endl;
	for (int k = 0; k < j; k++)
	{
		cout << Y[k] << " ";
	}
	cout << endl;
}