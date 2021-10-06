#include <iostream>
#include <fstream>
#include <iomanip>
#include "MinusOne.h"
using namespace std;

const char path[]{"prob1.dat"};
const int MAXLEN = 20;

struct field
{
	char HEI[MAXLEN]{};
	int students{};
	int faculties{};
};

void input();
void output();
void students();
char repeat();

void problem1()
{
	char c = '0';
	while (c == '0')
	{
		cout << "\tВУЗы" << endl << endl;

		ofstream clr(path, ios::binary);
		clr.close();
		cout << "Введите 10 ВУЗов:" << endl << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << i + 1 << "-й ВУЗ" << endl;
			input();
			cout << endl;
		}
		output();
		cout << endl;
		cout << "Введите еще 3 ВУЗа:" << endl << endl;
		for (int i = 0; i < 3; i++)
		{
			cout << i + 11 << "-й ВУЗ" << endl;
			input();
			cout << endl;
		}
		students();
		cout << endl;
		c = repeat();
		system("cls");
	}
}

void input()
{
	ofstream out(path, ios::binary | ios::app);
	field in{};

	cout << "Введите название ВУЗа: ";
	cin.getline(in.HEI, MAXLEN);
	
	cout << "Введите число студентов: ";
	cin >> in.students;

	cout << "Введите количество факультетов: ";
	cin >> in.faculties;

	out.write((char*)&in, sizeof(in));

	out.close();
	cin.ignore(32767, '\n');
}

void output()
{
	ifstream in(path, ios::binary);
	field out{};

	cout << "\tСодержимое файла" << endl << endl;
	cout << setw(20) << "Название ВУЗа" << " ";
	cout << setw(10) << "Студенты" << " ";
	cout << setw(10) << "Факультеты" << endl;
	
	while (in.tellg() != -1)
	{
		in.read((char*)&out, sizeof(out));
		cout << setw(20) << out.HEI << " ";
		cout << setw(10) << out.students << " ";
		cout << setw(10) << out.faculties << endl;
		minusone(in);
	}

	in.close();
}

void students()
{
	ifstream in(path, ios::binary);
	int sum = 0;
	while (in.tellg() != -1)
	{
		field out{};
		in.read((char*)&out, sizeof(out));
		sum += out.students;
		minusone(in);
	}
	cout << "Всего студентов: " << sum << endl;
}

char repeat()
{
	char res = '0';
	cout << "Введите 0 для запуска программы еще раз: ";
	cin.get(res);
	if (res == '0')
	{
		cin.get(res);
		if (res != '\n')
		{
			res = '1';
		}
		else
		{
			res = '0';
		}
	}
	else if (res != '\n')
	{
		cin.ignore(32767, '\n');
	}
	return res;
}