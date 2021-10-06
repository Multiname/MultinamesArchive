#include <iostream>
using namespace std;

const int MAXLEN = 255;

int mystrcspn(char str[], char keys[]);

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "������� ������: ";
	char str[MAXLEN]{};
	cin.getline(str, MAXLEN, '\n');
	cout << "������� ������ � ���������, ������� ����� �����: ";
	char keys[MAXLEN]{};
	cin.getline(keys, MAXLEN, '\n');
	cout << "�������� �� ������� ���������: "
		<< mystrcspn(str, keys) << endl;
}

int mystrcspn(char str[], char keys[])
{
	int slen = strlen(str);
	int klen = strlen(keys);
	bool find = false;
	int len = 0;
	while (!find)
	{
		for (int j = 0; j < klen + 1; j++)
		{
			if (str[len] == keys[j])
			{
				find = true;
			}
		}
		len++;
	}
	len--;
	return len;
}