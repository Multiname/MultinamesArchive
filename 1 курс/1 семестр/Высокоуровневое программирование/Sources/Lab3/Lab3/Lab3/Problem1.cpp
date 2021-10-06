#include <iostream>
using namespace std;

void main()
{
	for (float x = 0; x < 1.3; x += 0.1)
	{
		float y = sin(x) + pow(sin(x*x), 2) + 
			pow(sin(x*x*x), 3);
		cout << "f(" << x << ") = " << y << "\n";
	}
}