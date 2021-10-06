#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

int main()
{
	double numberOfInputData = 1000;
	double decrement = 2 / numberOfInputData;
	int N = 1000;

	double startTime = clock();

	for (double x = 1; x > -1; x -= decrement)
	{
		double ln{};
		for (unsigned short n = 1; n <= N; ++n)
		{
			ln += pow(-1, n + 1) * pow(x, n) / n;
		}
	}

	double endTime = clock();
	double workTime = endTime - startTime;
	cout << "Work time: " << workTime << '\n';

	return 0;
}