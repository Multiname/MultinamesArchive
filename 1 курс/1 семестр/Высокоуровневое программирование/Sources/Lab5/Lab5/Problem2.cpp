#include <iostream>
#include "Refresh.h"
using namespace std;

const int MAXLEN = 255;
const int BRAND = 50;
const int YEAR = 5;
const int COLOR = 15;
const int NUMBER = 10;

struct car
{
	char* date = new char[11] {"00.00.0000"};
	char* brand = new char[BRAND]{};
	char* year = new char[YEAR];
	char* color = new char[COLOR]{};
	char* number = new char[NUMBER]{};
};

void registration(car list[], int& len);
void output(car list[], int len);
void cardelete(car list[], int& len);
void carsearch(car list[], int len);

void problem2()
{
	cout << "\tАвтомашины" << endl << endl;
	car* list = new car[MAXLEN];
	int len = 0;

	int com{};
	while (com != 4)
	{
		cout << "Список команд:" << endl;
		cout << "   0. Вывод списка" << endl;
		cout << "   1. Добавление новой машины" << endl;
		cout << "   2. Удаление машины" << endl;
		cout << "   3. Поиск машины" << endl;
		cout << "   4. Выход" << endl << endl;
		cout << "Введите номер команды: ";
		cin >> com;
		refresh("Автомашины");
		switch (com)
		{
		case 0:
			output(list, len);
			break;
		case 1:
			registration(list, len);
			refresh("Автомашины");
			break;
		case 2:
			cardelete(list, len);
			cout << endl;
			break;
		case 3:
			carsearch(list, len);
			break;
		}
	}
	delete[] list;
}

void registration(car list[], int &len)
{
	car newcar;
	cout << "Введите дату регистрации машины в формате ДД:ММ:ГГГГ: ";
	cin >> newcar.date;
	cout << "Введите марку машины: ";
	cin >> newcar.brand;
	cout << "Введите год выпуска машины: ";
	cin >> newcar.year;
	cout << "Введите цвет машины: ";
	cin >> newcar.color;
	cout << "Введите номер машины: ";
	cin >> newcar.number;
	cout << endl;

	list[len] = newcar;
	len++;
}

void output(car list[], int len)
{
	cout << "Список машин: дата регистрации / марка / выпуск / цвет / номер" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << i << ". " << list[i].date << " / " << list[i].brand << " / " << list[i].year << " / " << list[i].color << " / " << list[i].number << endl;
	}
	cout << endl;
}

void cardelete(car list[], int& len)
{
	output(list, len);
	cout << "Введите номер машины, которую хотите удалить: ";
	int num{};
	cin >> num;
	if (num >= len || num < 0)
	{
		cout << "Данный номер отсутствует" << endl;
	}
	else
	{
		for (int i = num; i < len - 1; i++)
		{
			list[i] = list[i + 1];
		}
		list[len] = {};
		len--;
		refresh("Автомашины");
	}
}

void carsearch(car list[], int len)
{
	car search{};
	cout << "Заполните поля (если поле не используется в поиске, введите 0)" << endl;
	cout << "Дата регистрации: ";
	cin >> search.date;
	cout << "Марка: ";
	cin >> search.brand;
	cout << "Год выпуска: ";
	cin >> search.year;
	cout << "Цвет: ";
	cin >> search.color;
	cout << "Номер: ";
	cin >> search.number;

	cout << endl << "Удалось найти: " << endl;
	for (int i = 0; i < len; i++)
	{
		bool found = true;
		if (strcmp(search.date, "0") && strcmp(list[i].date, search.date))
		{
			found = false;
		}
		if (strcmp(search.brand, "0") && strcmp(list[i].brand, search.brand))
		{
			found = false;
		}
		if (strcmp(search.year, "0") && strcmp(list[i].year, search.year))
		{
			found = false;
		}
		if (strcmp(search.color, "0") && strcmp(list[i].color, search.color))
		{
			found = false;
		}
		if (strcmp(search.number, "0") && strcmp(list[i].number, search.number))
		{
			found = false;
		}

		if (found)
		{
			cout << list[i].date << " / " << list[i].brand << " / " << list[i].year << " / " << list[i].color << " / " << list[i].number << endl;
		}
	}
	cout << endl;
}