#include "Exam.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "\t������ �������� � �������� ��������\n\n";

	Exam* defaultIsaac = new Exam();
	Exam michaelGeometry = Exam("Michael", 130121, 5);
	Exam michaelMath = Exam(michaelGeometry);
	michaelMath.SetDate(190121);
	michaelMath.Print();
	delete defaultIsaac;

	cout << "\n\t����������� ��������� �� ������\n\n";

	Exam* ivanMath = new Exam("Ivan", 190121, 3);


	cout << "\n����������� ��������� �� ����� ������...\n\n";

	void (Exam::*printPointer) ();
	printPointer = &Exam::Print;


	cout << "\n\t������������� ��������� �� ������ ��� �������� �����\n";
	cout << "\t������������� ��������� �� ����� ��� ������ ����� ������\n\n";

	Exam *ivanGeometry = new Exam(*ivanMath);
	ivanGeometry->SetDate(130121);
	ivanGeometry->SetMark(4);
	(ivanGeometry->*printPointer)();


	cout << "\n\t�������� ������������ ������� ��������� �������\n";
	cout << "\t�������� ������������� ������� ��������� �����\n\n";

	Exam michaelExams[2]{michaelGeometry, michaelMath};
	Exam* ivanExams = new Exam[2]{*ivanGeometry, *ivanMath};

	
	cout << "\n\t����� ��������\n\n";

	for (int i = 0; i < 2; i++)
	{
		michaelExams[i].Print();
	}
	for (int i = 0; i < 2; i++)
	{
		ivanExams[i].Print();
	}


	cout << "\n\t������� ����\n\n";

	delete ivanMath;
	delete ivanGeometry;
	delete[] ivanExams;


	cout << "\n\t������� �����\n\n";

	return 0;
}