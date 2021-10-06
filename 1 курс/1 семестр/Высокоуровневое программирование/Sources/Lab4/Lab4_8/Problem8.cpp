#include <iostream>
using namespace std;

const int MAXLEN = 255;
const int ALPHALEN = 26;

bool findsymbol(char str[], char sym);
void sort(char str[]);
void myswap(char& a, char& b);

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "¬ведите текст: " << endl;
	char text[MAXLEN]{};
	cin.getline(text, MAXLEN, '\n');
	_strlwr_s(text);

	char Letters[ALPHALEN]{};
	int l = 0;
	char BlackList[ALPHALEN]{};
	int b = 0;
	for (int i = 0; i < strlen(text); i++)
	{
		if (isalpha(text[i]))
		{
			if (findsymbol(Letters, text[i]) &&
				!findsymbol(BlackList, text[i]))
			{
				BlackList[b] = text[i];
				b++;
			}
			else if (!findsymbol(Letters, text[i]))
			{
				Letters[l] = text[i];
				l++;
			}
		}
	}

	sort(Letters);

	cout << "Ѕуквы, встречающиес€ 1 раз: " << endl;
	for (int j = 0; j < strlen(Letters); j++)
	{
		if (!findsymbol(BlackList, Letters[j]))
		{
			cout << Letters[j] << " ";
		}
	}
	cout << endl;
}

bool findsymbol(char str[], char sym)
{
	bool find = false;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == sym)
		{
			find = true;
		}
	}
	return find;
}

void sort(char str[])
{
	bool check = true;
	int start = 0;
	int end = strlen(str) - 1;
	while (check)
	{
		check = false;
		for (int p = start; p < end; p++)
		{
			if (str[p] > str[p + 1])
			{
				check = true;
				myswap(str[p], str[p + 1]);
			}
		}
		start++;

		for (int q = end; q > start - 1; q--)
		{
			if (str[q] < str[q - 1])
			{
				check = true;
				myswap(str[q], str[q - 1]);
			}
		}
		end--;
	}
}

void myswap(char& a, char& b)
{
	char temp = a;
	a = b;
	b = temp;
}