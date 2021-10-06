#include <iostream>
using namespace std;

const int MAX_LEN = 255;
void main()
{
	setlocale(LC_ALL, "Russian");

	char str[MAX_LEN]{};
	cout << "¬ведите строку: " << endl;
	cin.getline(str, MAX_LEN, '\n');
	cout << endl;
	_strlwr_s(str);

	char first = str[0];
	char last{};
	char word[254]{};
	int num = 0;
	int j = 0;
	cout << "—лова с одинаковым началом и концом: " << endl;
	while (str[j] != ' ' && str[j] != '.')
	{
		word[j] = str[j];
		if (str[j + 1] == ' ' || str[j + 1] == '.')
		{
			last = str[j];
		}
		j++;
	}
	if (first == last)
	{
		num++;
		cout << word << " ";
	}
	int len = strlen(word);
	for (int k = 0; k < len; k++)
	{
		word[k] = {};
	}

	bool TimeToCheck = false;
	int n = 0;
	for (int i = j + 1; i < strlen(str) - 1; i++)
	{
		if (str[i] != ' ')
		{
			word[n] = str[i];
			n++;
		}
		if (str[i - 1] == ' ')
		{
			first = str[i];
		}
		if (str[i + 1] == ' ' || str[i + 1] == '.')
		{
			last = str[i];
			TimeToCheck = true;
		}
		if (TimeToCheck == true)
		{
			if (first == last)
			{
				num++;
				cout << word << " ";
			}
			TimeToCheck = false;
			int len0 = strlen(word);
			for (int y = 0; y < len0; y++)
			{
				word[y] = {};
			}
			n = 0;
		}
	}
	cout << endl;
	cout << "»х количество: " << num << endl;
}