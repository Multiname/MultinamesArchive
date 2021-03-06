#include <iostream>
using namespace std;

const int MAXLEN = 255;

void clear(char str[]);
int findmax(char str[], char strmax[][MAXLEN]);

void ma1234in()
{
	setlocale(LC_ALL, "Russian");

	char str1[MAXLEN]{};
	char str2[MAXLEN]{};
	cout << "??????? ?????? ??????: ";
	cin.getline(str1, MAXLEN);
	cout << "??????? ?????? ??????: ";
	cin.getline(str2, MAXLEN);

	char str1max[MAXLEN][MAXLEN]{};
	char str2max[MAXLEN][MAXLEN]{};

	bool find = false;
	int s1 = findmax(str1, str1max);
	int s2 = findmax(str2, str2max);
	cout << "????? ??????? ?????, ????? ??? ???? ?????:" << endl;
	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			if (!strcmp(str1max[i], str2max[j]))
			{
				find = true;
				cout << str1max[i] << endl;
			}
		}
	}
	if (!find)
	{
		cout << "???????????" << endl;
	}
}

void clear(char str[])
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		str[i] = {};
	}
}

int findmax(char str[], char strmax[][MAXLEN])
{
	char word[MAXLEN]{};
	int w = 0;
	int maxlen = 0;
	int s = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] != ' ')
		{
			word[w] = str[i];
			w++;
		}
		if (i == strlen(str) - 1 || str[i] == ' ')
		{
			if (strlen(word) == maxlen)
			{
				for (int j = 0; j < maxlen; j++)
				{
					strmax[s][j] = word[j];
				}
				s++;
			}
			else if (strlen(word) > maxlen)
			{
				maxlen = strlen(word);
				for (int j = 0; j < s; j++)
				{
					clear(strmax[j]);
				}
				s = 0;
				for (int j = 0; j < maxlen; j++)
				{
					strmax[s][j] = word[j];
				}
				s++;
			}
			clear(word);
			w = 0;
		}
	}
	return s;
}