#include <iostream>
#include <set>
#include "Exam.h"
#include <vector>
#include <algorithm>

using namespace std;

void RunFirst()
{
	multiset<int> container1{};

	cout << "Введите 7 целых чисел для первого контейнера\n";
	int input{};
	for (unsigned short i{}; i < 7; ++i)
	{
		cout << i + 1 << ": ";
		cin >> input;
		container1.insert(input);
	}

	cout << "\nСодержимое первого контейнера: ";
	multiset<int>::iterator iterator{};
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		cout << *iterator << " ";
	}
	cout << "\n";

	cout << "\nКакие 2 элемента (по значению) вы хотите удалить?\n";
	cout << "1: ";
	cin >> input;
	container1.erase(input);
	cout << "2: ";
	cin >> input;
	container1.erase(input);

	cout << "\nКакие 2 элемента (по значению) вы хотите заменить?\n";
	cout << "1: ";
	cin >> input;
	container1.erase(input);
	cout << "2: ";
	cin >> input;
	container1.erase(input);

	cout << "\nКакие 2 элемента вы хотите записать вместо них?\n";
	cout << "1: ";
	cin >> input;
	container1.insert(input);
	cout << "2: ";
	cin >> input;
	container1.insert(input);

	cout << "\nСодержимое первого контейнера: ";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		cout << *iterator << " ";
	}
	cout << "\n";

	multiset<int> container2{};

	cout << "\nВведите 3 целых числа для второго контейнера\n";
	for (unsigned short i{}; i < 3; ++i)
	{
		cout << i + 1 << ": ";
		cin >> input;
		container2.insert(input);
	}

	cout << "\nСколько элементов вы хотите удалить в первом контейнере?\n";
	cout << ">>> ";
	int length{};
	cin >> length;
	cout << "\nНачиная с какого элемента (по значению) произвести удаление?\n\n";
	cout << ">>> ";
	cin >> input;
	iterator = container1.find(input);
	for (int i = 0; i < length; ++i)
	{
		++iterator;
	}
	container1.erase(container1.find(input), iterator);

	container1.insert(container2.begin(), container2.end());
	cout << "\nСодержимое первого контейнера после объединения со вторым: ";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		cout << *iterator << " ";
	}
	cout << "\n";

	cout << "\nСодержимое второго контейнера: ";
	for (iterator = container2.begin(); iterator != container2.end(); ++iterator)
	{
		cout << *iterator << " ";
	}
	cout << "\n\n";
}

void RunSecond()
{
	multiset<Exam> container1{};

	cout << "Введите 4 экзамена для первого контейнера\n\n";
	for (unsigned short i{}; i < 4; ++i)
	{
		Exam exam = Exam();

		cout << "#" << i + 1 << "\n";

		cout << "Имя студента: ";
		char* name = new char[255];
		cin.getline(name, 255, '\n');
		exam.SetStudentName(name);
		delete[] name;

		cout << "Дата экзамена: ";
		int date{};
		cin >> date;
		exam.SetDate(date);

		cout << "Оценка: ";
		int mark{};
		cin >> mark;
		exam.SetMark(mark);
		cout << "\n";
		cin.ignore();

		container1.insert(exam);
	}

	cout << "\nСодержимое первого контейнера\n\n";
	multiset<Exam>::iterator iterator{};
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	int input{};
	cout << "\nКакой экзамен вы хотите удалить?\n";
	cout << ">>> ";
	cin >> input;
	iterator = container1.begin();
	for (int i = 0; i < input - 1; ++i)
	{
		++iterator;
	}
	container1.erase(iterator);

	cout << "\n\nСодержимое первого контейнера\n\n";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\nКакой экзамен вы хотите изменить?\n";
	cout << ">>> ";
	cin >> input;
	iterator = container1.begin();
	for (int i = 0; i < input - 1; ++i)
	{
		++iterator;
	}
	container1.erase(iterator);

	cout << "\nВведите новые данные\n\n";
	Exam newExam = Exam();

	cin.ignore();
	cout << "Имя студента: ";
	char* newName = new char[255];
	cin.getline(newName, 255, '\n');
	newExam.SetStudentName(newName);
	delete[] newName;

	cout << "Дата экзамена: ";
	int newDate{};
	cin >> newDate;
	newExam.SetDate(newDate);

	cout << "Оценка: ";
	int newMark{};
	cin >> newMark;
	newExam.SetMark(newMark);
	cout << "\n";

	container1.insert(newExam);

	cout << "\nСодержимое первого контейнера\n\n";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}
	cout << "\n";

	multiset<Exam> container2{};

	cout << "Введите 2 экзамена для второго контейнера\n\n";
	for (unsigned short i{}; i < 2; ++i)
	{
		Exam exam = Exam();

		cout << "#" << i + 1 << "\n";

		cin.ignore();
		cout << "Имя студента: ";
		char* name = new char[255];
		cin.getline(name, 255, '\n');
		exam.SetStudentName(name);
		delete[] name;

		cout << "Дата экзамена: ";
		int date{};
		cin >> date;
		exam.SetDate(date);

		cout << "Оценка: ";
		int mark{};
		cin >> mark;
		exam.SetMark(mark);
		cout << "\n";

		container2.insert(exam);
	}

	cout << "\nСколько экзаменов вы хотите удалить в первом контейнере?\n";
	cout << ">>> ";
	int length{};
	cin >> length;
	cout << "\nНачиная с какого элемента произвести удаление?\n";
	cout << ">>> ";
	cin >> input;
	cout << "\n";
	iterator = container1.begin();
	for (int i = 0; i < input - 1; ++i)
	{
		++iterator;
	}
	multiset<Exam>::iterator endIterator = iterator;
	for (int i = 0; i < length; ++i)
	{
		++endIterator;
	}
	container1.erase(iterator, endIterator);

	container1.insert(container2.begin(), container2.end());
	cout << "\nСодержимое первого контейнера после объединения со вторым\n\n";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\nСодержимое второго контейнера\n\n";
	for (iterator = container2.begin(); iterator != container2.end(); ++iterator)
	{
		(*iterator).Print();
	}
}

bool Compare(Exam& exam1, Exam& exam2)
{
	return exam1 > exam2;
}

bool IsPassed(Exam& exam)
{
	return exam.GetMark() > 2;
}

bool Is1(Exam& exam)
{
	return exam.GetMark() == 1;
}

void RunThird()
{
	vector<Exam> container1{};
	
	cout << "Введите 6 экзаменов для первого контейнера\n";
	for (unsigned short i{}; i < 6; ++i)
	{
		Exam* exam = new Exam();

		cout << "#" << i + 1 << "\n";

		cout << "Имя студента: ";
		char* name = new char[255];
		cin.getline(name, 255, '\n');
		exam->SetStudentName(name);
		delete[] name;

		cout << "Дата экзамена: ";
		int date{};
		cin >> date;
		exam->SetDate(date);

		cout << "Оценка: ";
		int mark{};
		cin >> mark;
		exam->SetMark(mark);
		cout << "\n";
		cin.ignore();

		container1.push_back(*exam);
	}

	sort(container1.begin(), container1.end(), Compare);

	cout << "\nСодержимое первого контейнера после сортировки\n\n";
	vector<Exam>::iterator iterator{};
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\nПервый сданный экзамен в первом контейнере\n\n";
	find_if(container1.begin(), container1.end(), IsPassed)->Print();

	vector<Exam> container2{};
	while (find_if(container1.begin(), container1.end(), IsPassed) != container1.end())
	{
		container2.push_back(*find_if(container1.begin(), container1.end(), IsPassed));
		container1.erase(find_if(container1.begin(), container1.end(), IsPassed));
	}

	cout << "\nСодержимое второго контейнера после переноса\nв него всех сданных экзаменов из первого контейнера\n\n";
	for (iterator = container2.begin(); iterator != container2.end(); ++iterator)
	{
		(*iterator).Print();
	}

	sort(container1.begin(), container1.end());
	sort(container2.begin(), container2.end());

	cout << "\nСодержимое первого контейнера после сортировки\n\n";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\nСодержимое второго контейнера после сортировки\n\n";
	for (iterator = container2.begin(); iterator != container2.end(); ++iterator)
	{
		(*iterator).Print();
	}

	vector<Exam> container3{};
	container3.insert(container3.end(), container1.begin(), container1.end());
	container3.insert(container3.end(), container2.begin(), container2.end());

	cout << "\nСодержимое третьего контейнера после слияния первого и второго\n\n";
	for (iterator = container3.begin(); iterator != container3.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\nКоличество сданных экзаменов: " << count_if(container3.begin(), container3.end(), IsPassed) << "\n";

	if (find_if(container3.begin(), container3.end(), Is1) != container3.end())
	{
		cout << "\nЕсть те, кто написал экзамен на 1\n";
	}
	else
	{
		cout << "\nНикто не написал экзамен на 1\n";
	}

	cout << "\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");

	unsigned short command = 1;
	while (command != 0)
	{
		cout << "====================================================\n\n";
		cout << "Какую задачу запустить?\n";
		cout << "1. Контейнеры со встроенным типом данных\n";
		cout << "2. Контейнеры с пользовательским типом данных\n";
		cout << "3. Алгоритмы\n";
		cout << "0. Выход\n";
		cout << ">> ";
		cin >> command;
		cout << "\n====================================================\n\n";
		cin.ignore();

		switch (command)
		{
		case 1:
			RunFirst();
			break;
		case 2:
			RunSecond();
			break;
		case 3:
			RunThird();
			break;
		}
	}

	return 0;
}