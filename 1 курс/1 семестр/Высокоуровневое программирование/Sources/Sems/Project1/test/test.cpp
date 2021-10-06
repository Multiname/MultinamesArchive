#include <iostream>
using namespace std;

void main()
{
	char c = '/';
	int sum = 0;
	if ((int)c >= 48 && (int)c <= 57)
	{
		sum += (int)c - 48;
		cout << sum << endl;
	}
}