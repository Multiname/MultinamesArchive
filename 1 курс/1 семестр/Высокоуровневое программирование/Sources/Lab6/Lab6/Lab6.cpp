#include <iostream>
#include "Menu.h"
#include "Problem1.h"
#include "Problem2.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	char* progname = new char[39] {"��������� ������ ������������� �������"};
	int probs = 2;
	const char** probname = new const char*[13] { "����", "�������" };
	void (*func[])() { problem1, problem2 };
	menu(progname, probs, probname, func);

	delete[] progname;
	delete[] probname;
	return 0;
}