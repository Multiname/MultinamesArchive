#include <iostream>
using namespace std;

void output(int num);

void mai122n()
{
	float Ff = -208.11;
	double Fd = -208.11;
	char str[10]{ "ABC" };
	bool* ptr = (bool*) &Ff;
	cout << "float: ";
	for (int i = 0; i < sizeof(Ff); i++)
	{
		output((*(ptr + i) / 16) % 16);
		output(*(ptr + i) % 16);
		cout << " ";
	}
	cout << endl << "double: ";
	ptr = (bool*)&Fd;
	for (int i = 0; i < sizeof(Fd); i++)
	{
		output((*(ptr + i) / 16) % 16);
		output(*(ptr + i) % 16);
		cout << " ";
	}
	cout << endl << "char[]: ";
	ptr = (bool*)str;
	for (int i = 0; i < sizeof(str); i++)
	{
		output((*(ptr + i) / 16) % 16);
		output(*(ptr + i) % 16);
		cout << " ";
	}
}

void output(int num)
{
	if (num > 9)
	{
		switch (num)
		{
		case 10:
			cout << "A";
			break;
		case 11:
			cout << "B";
			break;
		case 12:
			cout << "C";
			break;
		case 13:
			cout << "D";
			break;
		case 14:
			cout << "E";
			break;
		case 15:
			cout << "F";
			break;
		}
	}
	else
	{
		cout << num;
	}
}