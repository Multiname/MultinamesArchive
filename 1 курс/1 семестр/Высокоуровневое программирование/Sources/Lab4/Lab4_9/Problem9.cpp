#include <iostream>
using namespace std;

const int MAXLEN = 255;
const int ALPHALEN = 26;

void clear(char word[]);
bool findsymbol(char str[], char sym);

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите текст: " << endl;
	char Text[MAXLEN]{};
	cin.getline(Text, MAXLEN, '\n');

	int len = strlen(Text);
	char Word[MAXLEN]{};
	int w = 0;
	char Letters[MAXLEN]{};
	int l = 0;
	bool sorted = true;
	char WhiteList[ALPHALEN]{};
	int wl = 0;
	cout << "Слова, в которых буквы упорядочены по алфавиту"
		<<endl << "или каждая буква встречается больше раза: "
		<< endl;
	for (int i = 0; i < len - 1; i++)
	{
		if (isalnum(Text[i]))
		{
			Word[w] = Text[i];
			if (isalpha(Word[w]))
			{
				if (findsymbol(Letters, tolower(Word[w]))
					&& !findsymbol(WhiteList,
						tolower(Word[w])))
				{
					WhiteList[wl] = tolower(Word[w]);
					wl++;
				}
				Letters[l] = tolower(Word[w]);
				if (l != 0)
				{
					if (Letters[l - 1] > Letters[l])
					{
						sorted = false;
					}
				}
				l++;
			}
			w++;
			if (!isalnum(Text[i + 1]) && strlen(Word) != 0)
			{
				bool allmorethan1 = true;
				for (int i = 0; i < strlen(Letters); i++)
				{
					if (!findsymbol(WhiteList, Letters[i]))
					{
						allmorethan1 = false;
					}
				}
				if (sorted || allmorethan1)
				{
					cout << Word << " ";
				}
				sorted = true;
				clear(Word);
				w = 0;
				clear(Letters);
				l = 0;
				clear(WhiteList);
				wl = 0;
			}
		}
	}
	if (isalnum(Text[len - 1]))
	{
		Word[w] = Text[len - 1];
		if (isalpha(Word[w]))
		{
			if (findsymbol(Letters, tolower(Word[w])) &&
				!findsymbol(WhiteList, tolower(Word[w])))
			{
				WhiteList[wl] = tolower(Word[w]);
			}
			Letters[l] = tolower(Word[w]);
			if (l != 0)
			{
				if (Letters[l - 1] > Letters[l])
				{
					sorted = false;
				}
			}
		}
		bool allmorethan1 = true;
		for (int i = 0; i < strlen(Letters); i++)
		{
			if (!findsymbol(WhiteList, Letters[i]))
			{
				allmorethan1 = false;
			}
		}
		if (sorted || allmorethan1)
		{
			cout << Word << " ";
		}
	}
	cout << endl;
}

void clear(char word[])
{
	int len = strlen(word);
	for (int i = 0; i < len + 1; i++)
	{
		word[i] = {};
	}
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