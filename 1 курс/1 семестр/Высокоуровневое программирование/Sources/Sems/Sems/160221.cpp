// ��������� ����� ������������ ��������
// ������� ����� �������, ���, �������, 5 ������, ���������� �������� �����
// ������� � �������, ������������ ��� 3 ����, ����������

#include "Student.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	char* firstName = new char[6] {"Yarik"};
	char* secondName = new char[8] {"Timoxin"};
	int* marks = new int[5]{ 5, 5, 5, 5, 1 };

	Student Ivan = Student(firstName, secondName, marks, 5);
	Ivan.PrintInfo();
	cout << Ivan.GetAverageMark() << '\n';

	return 0;
}

/*
����������� ���������������� ������ � �++
�����
�������� �������
����� ������ �������
*/