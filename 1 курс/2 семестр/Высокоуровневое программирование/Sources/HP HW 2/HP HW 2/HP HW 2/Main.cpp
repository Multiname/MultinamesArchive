#include <iostream>
#include <set>
#include "Exam.h"
#include <vector>
#include <algorithm>

using namespace std;

void RunFirst()
{
	multiset<int> container1{};

	cout << "������� 7 ����� ����� ��� ������� ����������\n";
	int input{};
	for (unsigned short i{}; i < 7; ++i)
	{
		cout << i + 1 << ": ";
		cin >> input;
		container1.insert(input);
	}

	cout << "\n���������� ������� ����������: ";
	multiset<int>::iterator iterator{};
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		cout << *iterator << " ";
	}
	cout << "\n";

	cout << "\n����� 2 �������� (�� ��������) �� ������ �������?\n";
	cout << "1: ";
	cin >> input;
	container1.erase(input);
	cout << "2: ";
	cin >> input;
	container1.erase(input);

	cout << "\n����� 2 �������� (�� ��������) �� ������ ��������?\n";
	cout << "1: ";
	cin >> input;
	container1.erase(input);
	cout << "2: ";
	cin >> input;
	container1.erase(input);

	cout << "\n����� 2 �������� �� ������ �������� ������ ���?\n";
	cout << "1: ";
	cin >> input;
	container1.insert(input);
	cout << "2: ";
	cin >> input;
	container1.insert(input);

	cout << "\n���������� ������� ����������: ";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		cout << *iterator << " ";
	}
	cout << "\n";

	multiset<int> container2{};

	cout << "\n������� 3 ����� ����� ��� ������� ����������\n";
	for (unsigned short i{}; i < 3; ++i)
	{
		cout << i + 1 << ": ";
		cin >> input;
		container2.insert(input);
	}

	cout << "\n������� ��������� �� ������ ������� � ������ ����������?\n";
	cout << ">>> ";
	int length{};
	cin >> length;
	cout << "\n������� � ������ �������� (�� ��������) ���������� ��������?\n\n";
	cout << ">>> ";
	cin >> input;
	iterator = container1.find(input);
	for (int i = 0; i < length; ++i)
	{
		++iterator;
	}
	container1.erase(container1.find(input), iterator);

	container1.insert(container2.begin(), container2.end());
	cout << "\n���������� ������� ���������� ����� ����������� �� ������: ";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		cout << *iterator << " ";
	}
	cout << "\n";

	cout << "\n���������� ������� ����������: ";
	for (iterator = container2.begin(); iterator != container2.end(); ++iterator)
	{
		cout << *iterator << " ";
	}
	cout << "\n\n";
}

void RunSecond()
{
	multiset<Exam> container1{};

	cout << "������� 4 �������� ��� ������� ����������\n\n";
	for (unsigned short i{}; i < 4; ++i)
	{
		Exam exam = Exam();

		cout << "#" << i + 1 << "\n";

		cout << "��� ��������: ";
		char* name = new char[255];
		cin.getline(name, 255, '\n');
		exam.SetStudentName(name);
		delete[] name;

		cout << "���� ��������: ";
		int date{};
		cin >> date;
		exam.SetDate(date);

		cout << "������: ";
		int mark{};
		cin >> mark;
		exam.SetMark(mark);
		cout << "\n";
		cin.ignore();

		container1.insert(exam);
	}

	cout << "\n���������� ������� ����������\n\n";
	multiset<Exam>::iterator iterator{};
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	int input{};
	cout << "\n����� ������� �� ������ �������?\n";
	cout << ">>> ";
	cin >> input;
	iterator = container1.begin();
	for (int i = 0; i < input - 1; ++i)
	{
		++iterator;
	}
	container1.erase(iterator);

	cout << "\n\n���������� ������� ����������\n\n";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\n����� ������� �� ������ ��������?\n";
	cout << ">>> ";
	cin >> input;
	iterator = container1.begin();
	for (int i = 0; i < input - 1; ++i)
	{
		++iterator;
	}
	container1.erase(iterator);

	cout << "\n������� ����� ������\n\n";
	Exam newExam = Exam();

	cin.ignore();
	cout << "��� ��������: ";
	char* newName = new char[255];
	cin.getline(newName, 255, '\n');
	newExam.SetStudentName(newName);
	delete[] newName;

	cout << "���� ��������: ";
	int newDate{};
	cin >> newDate;
	newExam.SetDate(newDate);

	cout << "������: ";
	int newMark{};
	cin >> newMark;
	newExam.SetMark(newMark);
	cout << "\n";

	container1.insert(newExam);

	cout << "\n���������� ������� ����������\n\n";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}
	cout << "\n";

	multiset<Exam> container2{};

	cout << "������� 2 �������� ��� ������� ����������\n\n";
	for (unsigned short i{}; i < 2; ++i)
	{
		Exam exam = Exam();

		cout << "#" << i + 1 << "\n";

		cin.ignore();
		cout << "��� ��������: ";
		char* name = new char[255];
		cin.getline(name, 255, '\n');
		exam.SetStudentName(name);
		delete[] name;

		cout << "���� ��������: ";
		int date{};
		cin >> date;
		exam.SetDate(date);

		cout << "������: ";
		int mark{};
		cin >> mark;
		exam.SetMark(mark);
		cout << "\n";

		container2.insert(exam);
	}

	cout << "\n������� ��������� �� ������ ������� � ������ ����������?\n";
	cout << ">>> ";
	int length{};
	cin >> length;
	cout << "\n������� � ������ �������� ���������� ��������?\n";
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
	cout << "\n���������� ������� ���������� ����� ����������� �� ������\n\n";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\n���������� ������� ����������\n\n";
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
	
	cout << "������� 6 ��������� ��� ������� ����������\n";
	for (unsigned short i{}; i < 6; ++i)
	{
		Exam* exam = new Exam();

		cout << "#" << i + 1 << "\n";

		cout << "��� ��������: ";
		char* name = new char[255];
		cin.getline(name, 255, '\n');
		exam->SetStudentName(name);
		delete[] name;

		cout << "���� ��������: ";
		int date{};
		cin >> date;
		exam->SetDate(date);

		cout << "������: ";
		int mark{};
		cin >> mark;
		exam->SetMark(mark);
		cout << "\n";
		cin.ignore();

		container1.push_back(*exam);
	}

	sort(container1.begin(), container1.end(), Compare);

	cout << "\n���������� ������� ���������� ����� ����������\n\n";
	vector<Exam>::iterator iterator{};
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\n������ ������� ������� � ������ ����������\n\n";
	find_if(container1.begin(), container1.end(), IsPassed)->Print();

	vector<Exam> container2{};
	while (find_if(container1.begin(), container1.end(), IsPassed) != container1.end())
	{
		container2.push_back(*find_if(container1.begin(), container1.end(), IsPassed));
		container1.erase(find_if(container1.begin(), container1.end(), IsPassed));
	}

	cout << "\n���������� ������� ���������� ����� ��������\n� ���� ���� ������� ��������� �� ������� ����������\n\n";
	for (iterator = container2.begin(); iterator != container2.end(); ++iterator)
	{
		(*iterator).Print();
	}

	sort(container1.begin(), container1.end());
	sort(container2.begin(), container2.end());

	cout << "\n���������� ������� ���������� ����� ����������\n\n";
	for (iterator = container1.begin(); iterator != container1.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\n���������� ������� ���������� ����� ����������\n\n";
	for (iterator = container2.begin(); iterator != container2.end(); ++iterator)
	{
		(*iterator).Print();
	}

	vector<Exam> container3{};
	container3.insert(container3.end(), container1.begin(), container1.end());
	container3.insert(container3.end(), container2.begin(), container2.end());

	cout << "\n���������� �������� ���������� ����� ������� ������� � �������\n\n";
	for (iterator = container3.begin(); iterator != container3.end(); ++iterator)
	{
		(*iterator).Print();
	}

	cout << "\n���������� ������� ���������: " << count_if(container3.begin(), container3.end(), IsPassed) << "\n";

	if (find_if(container3.begin(), container3.end(), Is1) != container3.end())
	{
		cout << "\n���� ��, ��� ������� ������� �� 1\n";
	}
	else
	{
		cout << "\n����� �� ������� ������� �� 1\n";
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
		cout << "����� ������ ���������?\n";
		cout << "1. ���������� �� ���������� ����� ������\n";
		cout << "2. ���������� � ���������������� ����� ������\n";
		cout << "3. ���������\n";
		cout << "0. �����\n";
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