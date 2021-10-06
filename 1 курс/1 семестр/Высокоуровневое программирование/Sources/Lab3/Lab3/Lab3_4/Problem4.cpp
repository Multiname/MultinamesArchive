#include <iostream>
using namespace std;

const int MAX_LEN_OT = 255;
void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите текст (на англ.): ";
	char text[MAX_LEN_OT]{};
	cin.getline(text, MAX_LEN_OT, '\n');
	int len = strlen(text);

	int NumOW = 0;

	if (text[0] == 'a' || text[0] == 'A')
	{
		NumOW++;
	}

	for (int i = 1; i < len; i++)
	{
		if (text[i-1] == ' ')
		{
			if (text[i] == 'a' || text[i] == 'A')
			{
				NumOW++;
			}
		}
	}

	if (NumOW == 0)
	{
		cout << "Слов на букву А нет " << endl;
	}
	else
	{
		cout << "Количество слов на букву А: "
			<< NumOW << endl;
	}
}