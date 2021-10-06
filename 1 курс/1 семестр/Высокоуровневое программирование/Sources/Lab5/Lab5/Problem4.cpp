#include <iostream>
#include <fstream>
#include "Refresh.h"
#include <string.h>
using namespace std;

const int MAXLENOFFIELD = 50;
const int MAXLENOFLINE = 255;
const int CIPHER = 4;

void add(const char path[]);
void write(bool end, const char path[]);
void erase();
void showlist();
void change();
void info();
void table(char line[], bool nameline);
void showlistupg();

void problem4()
{
	cout << "\tБиблиотека" << endl << endl;
	int com{};
	while (com != 5)
	{
		cout << "Список команд:" << endl;
		cout << "   0. Список всех книг" << endl;
		cout << "   1. Добавить книгу" << endl;
		cout << "   2. Удалить книгу" << endl;
		cout << "   3. Изменить запись" << endl;
		cout << "   4. Получить информацию о книге" << endl;
		cout << "   5. Выход" << endl << endl;
		cout << "Введите команду: ";
		cin >> com;
		refresh("Библиотека");
		switch (com)
		{
		case 0:
			showlistupg();
			cout << endl;
			break;
		case 1:
			add("books.txt");
			refresh("Библиотека");
			break;
		case 2:
			erase();
			refresh("Библиотека");
			break;
		case 3:
			change();
			refresh("Библиотека");
			break;
		case 4:
			info();
			cout << endl;
			break;
		}
	}
}

void add(const char path[])
{
	cin.ignore(32767, '\n');
	cout << "Введите шифр (напр., 001): ";
	write(false, path);
	cout << "Введите автора: ";
	write(false, path);
	cout << "Введите название: ";
	write(false, path);
	cout << "Введите год издания: ";
	write(false, path);
	cout << "Введите стеллаж:полку (напр., 12:34): ";
	write(true, path);
}

void erase()
{
	cout << "Введите шифр книги, которую нужно удалить: ";
	char* cipher = new char[CIPHER] {};
	cin >> cipher;
	char* line = new char[MAXLENOFLINE] {};
	fstream file;
	file.open("books.txt");
	fstream temp;
	temp.open("temp.txt", ios::out);
	bool found = false;
	file.getline(line, MAXLENOFLINE, '/');
	while (!file.eof())
	{
		if (strcmp(line, cipher))
		{
			file.seekg(-4, ios_base::cur);
			file.getline(line, MAXLENOFLINE, '\n');
			temp << line;
			temp << '\n';
		}
		else
		{
			found = true;
			file.getline(line, MAXLENOFLINE, '\n');
		}
		file.getline(line, MAXLENOFLINE, '/');
	}
	file.close();
	temp.close();
	if (found)
	{
		file.open("books.txt", ios::out);
		temp.open("temp.txt");
		temp.getline(line, MAXLENOFLINE, '\n');
		while (!temp.eof())
		{
			file << line;
			file << '\n';
			temp.getline(line, MAXLENOFLINE, '\n');
		}
		file.close();
		temp.close();
	}
	else
	{
		cout << "Книга не найдена" << endl;
		char buf{};
		cin.get(buf);
		cin.ignore(32767, '\n');
	}
	delete[] cipher;
	delete[] line;
}

void write(bool end, const char path[])
{
	fstream file;
	char* str = new char[MAXLENOFFIELD] {};
	cin.getline(str, MAXLENOFFIELD);
	file.open(path, ios::app);
	file << str;
	end ? file << "\n" : file << "/";
	file.close();
	delete[] str;
}

void showlist()
{
	fstream file;
	file.open("books.txt");
	char* line = new char[MAXLENOFLINE] {};
	file.getline(line, MAXLENOFLINE, '\n');
	while (!file.eof())
	{
		cout << line << endl;
		file.getline(line, MAXLENOFLINE, '\n');
	}
	file.close();
}

void change()
{
	cin.ignore(32767, '\n');
	char* author = new char[MAXLENOFFIELD] {};
	char* name = new char[MAXLENOFFIELD] {};
	cout << "Введите автора: ";
	cin.getline(author, MAXLENOFFIELD);
	cout << "Введите название книги: ";
	cin.getline(name, MAXLENOFFIELD);

	char* field = new char[MAXLENOFLINE] {};
	char* line = new char[MAXLENOFLINE] {};
	fstream bks;
	bks.open("books.txt");
	fstream temp;
	temp.open("temp.txt", ios::out);
	fstream tempread;
	tempread.open("books.txt");
	bool found = false;
	tempread.getline(line, MAXLENOFLINE, '\n');
	while (!tempread.eof())
	{
		bks.getline(field, MAXLENOFLINE, '/');
		bks.getline(field, MAXLENOFLINE, '/');
		if (!strcmp(field, author) && !found)
		{
			bks.getline(field, MAXLENOFLINE, '/');
			if (!strcmp(field, name))
			{
				found = true;
				cout << "Запись найдена, введите новые значения" << endl;
				temp.close();
				add("temp.txt");
				temp.open("temp.txt", ios::app);
			}
			else
			{
				temp << line << '\n';
			}
		}
		else
		{
			temp << line << '\n';
		}
		bks.getline(field, MAXLENOFLINE, '\n');
		tempread.getline(line, MAXLENOFLINE, '\n');
	}
	delete[] author;
	delete[] name;
	delete[] field;
	bks.close();
	temp.close();
	if (found)
	{
		bks.open("books.txt", ios::out);
		temp.open("temp.txt");
		temp.getline(line, MAXLENOFLINE, '\n');
		while (!temp.eof())
		{
			bks << line;
			bks << '\n';
			temp.getline(line, MAXLENOFLINE, '\n');
		}
	}
	else
	{
		cout << "Книга не найдена" << endl;
		char buf{};
		cin.get(buf);
		if (buf != '\n')
		{
			cin.ignore(32767, '\n');
		}
	}
	delete[] line;
}

void info()
{
	char* cipher = new char[CIPHER] {};
	cout << "Введите шифр: ";
	cin >> cipher;
	char* str = new char[MAXLENOFLINE] {};
	fstream file;
	file.open("books.txt");
	file.getline(str, MAXLENOFLINE, '/');
	bool found = false;
	while (!file.eof() && !found)
	{
		if (!strcmp(str, cipher))
		{
			found = true;
			file.seekg(-4, ios_base::cur);
			file.getline(str, MAXLENOFLINE, '\n');
			cout << str << endl;
		}
		file.getline(str, MAXLENOFLINE, '\n');
		file.getline(str, MAXLENOFLINE, '/');
	}
	if (!found)
	{
		cout << "Книга не найдена" << endl;
	}
}

void table(char line[], bool nameline)
{
	if (nameline == true)
	{

	}
}

void showlistupg()
{
	int authormax = 6;
	int namemax = 4;
	ifstream rd("books.txt");
	char* line = new char[MAXLENOFFIELD] {};
	rd.getline(line, MAXLENOFFIELD, '/');
	while (!rd.eof())
	{
		rd.getline(line, MAXLENOFFIELD, '/');
		if (strlen(line) > authormax)
		{
			authormax = strlen(line);
		}
		rd.getline(line, MAXLENOFFIELD, '/');
		if (strlen(line) > namemax)
		{
			namemax = strlen(line);
		}
		rd.getline(line, MAXLENOFFIELD, '\n');
		rd.getline(line, MAXLENOFFIELD, '/');
	}
	rd.close();

	char* graph = new char[MAXLENOFLINE] {"+----+"};
	for (int i = 0; i < authormax; i++)
	{
		graph[6 + i] = '-';
	}
	graph[6 + authormax] = '+';
	for (int i = 0; i < namemax; i++)
	{
		graph[7 + authormax + i] = '-';
	}
	cout << graph << "+----+-----+" << endl;

	cout << "|code|";
	for (int i = 0; i < authormax - 6; i++)
	{
		cout << ' ';
	}
	cout << "author|";
	for (int i = 0; i < namemax - 4; i++)
	{
		cout << ' ';
	}
	cout << "name|year|place|" << endl;

	cout << graph << "+----+-----+" << endl;

	rd.open("books.txt");
	rd.getline(line, MAXLENOFFIELD, '/');
	while (!rd.eof())
	{
		for (int i = 0; i < 3; i++)
		{
			cout << "|";
			if (i == 0)
			{
				cout << ' ' << line;
			}
			else if (i == 1)
			{
				for (int j = 0; j < authormax - strlen(line); j++)
				{
					cout << ' ';
				}
				cout << line;
			}
			else if (i == 2)
			{
				for (int j = 0; j < namemax - strlen(line); j++)
				{
					cout << ' ';
				}
				cout << line;
			}
			rd.getline(line, MAXLENOFFIELD, '/');
		}
		cout << "|" << line;
		rd.getline(line, MAXLENOFFIELD, '\n');
		cout << "|" << line << "|" << endl;
		cout << graph << "+----+-----+" << endl;


		rd.getline(line, MAXLENOFFIELD, '/');
	}

	rd.close();
	delete[] line;
}