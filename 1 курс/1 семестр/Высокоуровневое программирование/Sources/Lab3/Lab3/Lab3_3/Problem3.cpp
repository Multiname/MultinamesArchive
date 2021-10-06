#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	for (int num = 1000; num < 10000; num++)
	{
		if(num % 11 == 0 and num % 7 == 0 and num % 2 == 0)
		{
			int sum = num % 10;
			sum += (num / 10) % 10;
			sum += (num / 100) % 10;
			sum += num / 1000;
			if (sum == 30)
			{
				int num_dup = num;
				int NumOfDig[10]{};
				for (int j = 0; j < 4; j++)
				{
					int dig = num_dup % 10;
					NumOfDig[dig] += 1;
					num_dup = num_dup / 10;
				}
				int DifNum = 0;
				for (int k = 0; k < 10; k++)
				{
					if (NumOfDig[k] != 0)
					{
						DifNum++;
					}
				}
				if (DifNum == 2)
				{
					cout << "Искомый номер: "
						<< num << endl;
				}
			}
		}
	}
}