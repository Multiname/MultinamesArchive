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
	cout << "\t����������" << endl << endl;
	car* list = new car[MAXLEN];
	int len = 0;

	int com{};
	while (com != 4)
	{
		cout << "������ ������:" << endl;
		cout << "   0. ����� ������" << endl;
		cout << "   1. ���������� ����� ������" << endl;
		cout << "   2. �������� ������" << endl;
		cout << "   3. ����� ������" << endl;
		cout << "   4. �����" << endl << endl;
		cout << "������� ����� �������: ";
		cin >> com;
		refresh("����������");
		switch (com)
		{
		case 0:
			output(list, len);
			break;
		case 1:
			registration(list, len);
			refresh("����������");
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
	cout << "������� ���� ����������� ������ � ������� ��:��:����: ";
	cin >> newcar.date;
	cout << "������� ����� ������: ";
	cin >> newcar.brand;
	cout << "������� ��� ������� ������: ";
	cin >> newcar.year;
	cout << "������� ���� ������: ";
	cin >> newcar.color;
	cout << "������� ����� ������: ";
	cin >> newcar.number;
	cout << endl;

	list[len] = newcar;
	len++;
}

void output(car list[], int len)
{
	cout << "������ �����: ���� ����������� / ����� / ������ / ���� / �����" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << i << ". " << list[i].date << " / " << list[i].brand << " / " << list[i].year << " / " << list[i].color << " / " << list[i].number << endl;
	}
	cout << endl;
}

void cardelete(car list[], int& len)
{
	output(list, len);
	cout << "������� ����� ������, ������� ������ �������: ";
	int num{};
	cin >> num;
	if (num >= len || num < 0)
	{
		cout << "������ ����� �����������" << endl;
	}
	else
	{
		for (int i = num; i < len - 1; i++)
		{
			list[i] = list[i + 1];
		}
		list[len] = {};
		len--;
		refresh("����������");
	}
}

void carsearch(car list[], int len)
{
	car search{};
	cout << "��������� ���� (���� ���� �� ������������ � ������, ������� 0)" << endl;
	cout << "���� �����������: ";
	cin >> search.date;
	cout << "�����: ";
	cin >> search.brand;
	cout << "��� �������: ";
	cin >> search.year;
	cout << "����: ";
	cin >> search.color;
	cout << "�����: ";
	cin >> search.number;

	cout << endl << "������� �����: " << endl;
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