#include <iostream>
using namespace std;

void main()
{
	cout << "A B C F" << endl;

	for (int a = 0; a < 2; a++)
	{
		bool A{};
		a == 1 ? A = true : A = false;

		for (int b = 0; b < 2; b++)
		{
			bool B{};
			b == 1 ? B = true : B = false;

			for (int c = 0; c < 2; c++)
			{
				bool C{};
				c == 1 ? C = true : C = false;

				bool F = (!(A | B)) & (A != C);
				cout << A << " " << B << " " << C << " " << F << endl;
			}
		}
	}
}