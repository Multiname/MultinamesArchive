#include <iostream>
using namespace std;

const int TXTLEN = 255;
void main()
{
	setlocale(LC_ALL, "Russian");

	char text[TXTLEN]{};
	cout <<
		"Введите текст, состоящий только из цифр и англ. букв:	"
		<< endl;
	cin.getline(text, TXTLEN, '\n');

	int curtxtlen = strlen(text);
	int sum = 0;

	for (int i = 0; i < curtxtlen; i++)
	{
		if ((int)text[i] >= 48 && (int)text[i] <= 57)
		{
			sum += (int)text[i] - 48;
		}
	}

	if (sum == curtxtlen)
	{
		cout << "Сумма цифр текста равна его длине" << endl;
	}
	else
	{
		cout << "Сумма цифр текста не равна его длине" << endl;
	}
}