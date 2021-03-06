#include "Student.h"
#include <iostream>

using namespace std;

const int MAXIMUM_LENGTH_OF_NAMES = 255;

Student::Student()
{
	m_firstName = new char[MAXIMUM_LENGTH_OF_NAMES];
	strcpy_s(m_firstName, MAXIMUM_LENGTH_OF_NAMES, "Ivan");
	m_secondName = new char[MAXIMUM_LENGTH_OF_NAMES];
	strcpy_s(m_secondName, MAXIMUM_LENGTH_OF_NAMES, "Ivanov");
	m_numberOfMarks = 5;
	m_marks = new int[m_numberOfMarks] { 1, 2, 3, 4, 5 };
}

Student::Student(char* firstName, char* secondName, int* marks, int numberOfMarks)
{
	m_firstName = firstName;
	m_secondName = secondName;
	m_numberOfMarks = numberOfMarks;
	m_marks = marks;
}

Student::Student(Student * student)
{
	m_firstName = student->GetFirstName();
	m_secondName = student->GetSecondName();
	m_numberOfMarks = student->GetNumberOfMarks();
	m_marks = student->GetMarks();
}

Student::~Student()
{
	delete[] m_firstName;
	delete[] m_secondName;
	delete[] m_marks;
}

void Student::SetFirstName(char* firstName)
{
	m_firstName = firstName;
}

void Student::SetSecondName(char* secondName)
{
	m_secondName = secondName;
}

int Student::SetMarks(int* marks)
{
	for (int i = 0; i < m_numberOfMarks; i++)
	{
		if (marks[i] < 1 || marks[i] > 5)
		{
			return -1;
		}
	}

	for (int i = 0; i < m_numberOfMarks; i++)
	{
		m_marks[i] = marks[i];
	}

	return 0;
}

void Student::SetNumberOfMarks(int numberOfMarks)
{
	m_numberOfMarks = numberOfMarks;
}

char* Student::GetFirstName()
{
	return m_firstName;
}

char* Student::GetSecondName()
{
	return m_secondName;
}

int* Student::GetMarks()
{
	return m_marks;
}

int Student::GetNumberOfMarks()
{
	return m_numberOfMarks;
}

float Student::GetAverageMark()
{
	float sum = 0;

	for (int i = 0; i < m_numberOfMarks; i++)
	{
		sum += m_marks[i];
	}
	
	return sum / m_numberOfMarks;
}

void Student::PrintInfo()
{
	cout << "???: " << m_firstName << '\n';
	cout << "???????: " << m_secondName << '\n';
	cout << "??????: ";
	for (int i = 0; i < m_numberOfMarks; i++)
	{
		cout << m_marks[i] << ' ';
	}
	cout << '\n';
}