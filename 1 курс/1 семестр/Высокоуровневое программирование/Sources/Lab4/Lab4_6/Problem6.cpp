#include <iostream>
using namespace std;

const int MAXLEN = 255;

void clear(char word[], int len);

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите строку: " << endl;
	char str[MAXLEN]{};
	cin.getline(str, MAXLEN, '\n');

	int len = strlen(str);
	char num[MAXLEN]{};
	int n = 0;
	int seven = 0;
	bool exist = false;
	cout << "Числа, содержащие не более двух 7: " << endl;
	for (int i = 0; i < len - 1; i++)
	{
		if (isdigit(str[i]))
		{
			if (str[i] == '7')
			{
				seven++;
			}
			num[n] = str[i];
			n++;
			if (isalpha(str[i + 1]))
			{
				if (seven < 3)
				{
					exist = true;
					cout << num << " ";
				}
				seven = 0;
				clear(num, len);
				n = 0;
			}
		}
	}
	if (isdigit(str[len - 1]))
	{
		if (str[len - 1] == '7')
		{
			seven++;
		}
		num[n] = str[len - 1];
		if (seven < 3)
		{
			exist = true;
			cout << num;
		}
	}
	if (!exist)
	{
		cout << "Отсутствуют" << endl;
	}
	cout << endl;
}

void clear(char word[], int len)
{
	for (int i = 0; i < len + 1; i++)
	{
		word[i] = {};
	}
}