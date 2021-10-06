#include <iostream>
using namespace std;

int findmaxnumofunits(int beg, int end);

void main()
{
	setlocale(LC_ALL, "Russian");

	int beg{};
	cout << "������� ������ ���������: ";
	cin >> beg;
	int end{};
	cout << "������� ����� ���������: ";
	cin >> end;
	cout << "����� � ������������ ����������� ������"
		<< endl <<"� �������� �������������: "
		<< findmaxnumofunits(beg, end) << endl;
}

int findmaxnumofunits(int beg, int end)
{

	int maxnum = 0;
	int maxunit = -1;

	for (int i = beg; i < end; i++)
	{
		int num = i;
		int numofunit = 0;
		while (num != 0)
		{
			if (num % 2 == 1)
			{
				numofunit++;
			}
			num = num / 2;
		}
		if (numofunit >= maxunit)
		{
			maxnum = i;
			maxunit = numofunit;
		}
	}

	return maxnum;
}