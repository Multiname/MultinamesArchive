#include <iostream>
#include "Menu.h"
#include "Problem1.h"
#include "Problem2.h"
#include "Problem3.h"
#include "Problem4.h"
#include "Problem5.h"
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	char* name = new char[54]{ "��������� �������� � ������ ����������������� �������" };
	int nop = 5;
	char* p1 = new char[9]{ "����_���" };
	char* p2 = new char[11]{ "����������" };
	char* p3 = new char[18]{ "����������� �����" };
	char* p4 = new char[11]{ "����������" };
	char* p5 = new char[14]{ "����� � �����" };
	char** ptrs = new char* [sizeof(p1) + sizeof(p2) + sizeof(p3) + sizeof(p4) + sizeof(p5)]{ p1, p2, p3, p4, p5 };
	
	void (*fcnptrs[])() { problem1, problem2, problem3, problem4, problem5 };
	menu(name, nop, ptrs, fcnptrs);

	delete[] p1;
	delete[] p2;
	delete[] p3;
	delete[] p4;
	delete[] p5;
	delete[] ptrs;
}