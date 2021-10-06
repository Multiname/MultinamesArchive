#include <iostream>
using namespace std;

const int MAXLEN = 255;

void display(char progname[], int probs, char* probname[]);
int digcheck(char str[]);

void menu(char progname[], int probs, char* probname[], void (*prog[])())
{
	display(progname, probs, probname);

	char* input = new char[MAXLEN] {};
	int num{};
	while (num != probs)
	{
		cout << "������� ���: ";
		do
		{
			cin >> input;
			cin.ignore(32767, '\n');
			num = digcheck(input);
			if (num > probs || num < 0)
			{
				display(progname, probs, probname);
				cout << "������������ ���, ���������� ��� ���: ";
			}
		} while (num > probs || num < 0);
		if (num != probs)
		{
			system("cls");
			prog[num]();
			display(progname, probs, probname);
		}
	}
	delete[] input;
}

void display(char progname[],int probs, char* probname[])
{
	system("cls");
	cout << "\t" << progname << endl << endl;
	cout << "�������:" << endl;
	for (int i = 0; i < probs; i++)
	{
		cout << "   " << i << ". " << probname[i] << endl;
	}
	cout << "   " << probs << ". �����" << endl;
}

int digcheck(char str[])
{
	bool alldigit = true;
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isdigit(str[i]))
		{
			alldigit = false;
		}
	}
	if (alldigit)
	{
		return atoi(str);
	}
	else
	{
		return -1;
	}
}