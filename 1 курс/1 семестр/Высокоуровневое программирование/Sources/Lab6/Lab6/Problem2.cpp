#include <iostream>
#include <fstream>
#include "MinusOne.h"
using namespace std;

const char path[]{"prob2.dat"};

void addarr();
void readarr(bool mode);

void problem2()
{
	cout << "\tМассивы" << endl << endl;

	int code = 0;
	while (code != 3)
	{
		cout << "   0. Добавить массив" << endl
			<< "   1. Узнать длину массива" << endl
			<< "   2. Узнать содержимое массива" << endl
			<< "   3. Выход" << endl << endl
			<< "Введите код: ";
		cin >> code;
		system("cls");
		cout << "\tМассивы" << endl << endl;
		switch (code)
		{
		case 0:
			addarr();
			break;
		case 1:
			readarr(false);
			break;
		case 2:
			readarr(true);
			break;
		}
	}
}

void addarr()
{
	int len{};
	ofstream file(path, ios::binary | ios::app);
	cout << "Введите длину массива: ";
	cin >> len;
	file.write((char*)&len, sizeof(len));

	cout << "Введите элементы:" << endl;
	for (int i = 0; i < len; i++)
	{
		int num{};
		cout << i << ". ";
		cin >> num;
		file.write((char*)&num, sizeof(num));
	}
	cout << endl;
	file.close();
}

void readarr(bool mode)
{
	cout << "Введите порядковый номер массива: ";
	int num{};
	cin >> num;
	if (num < 0)
	{
		cout << "Неправильный номер" << endl;
	}
	else
	{
		ifstream file(path, ios::binary);
		int i = 0;
		minusone(file);
		while (file.tellg() != -1 && i < num)
		{
			int len{};
			file.read((char*)&len, sizeof(len));
			file.seekg(len*sizeof(int), ios_base::cur);
			i++;
			minusone(file);
		}
		if (file.tellg() != -1 && i == num)
		{
			int len{};
			file.read((char*)&len, sizeof(len));
			if (mode == false)
			{
				cout << "Длина " << i << "-го массива: " << len << endl;
			}
			else
			{
				for (int j = 0; j < len; j++)
				{
					int elem{};
					file.read((char*)&elem, sizeof(elem));
					cout << j << ". " << elem << endl;
				}
			}
		}
		else
		{
			cout << "Массив не найден" << endl;
		}
		cout << endl;
		file.close();
	}
}