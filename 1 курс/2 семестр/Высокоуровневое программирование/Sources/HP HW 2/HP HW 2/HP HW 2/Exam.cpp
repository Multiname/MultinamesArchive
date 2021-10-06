#include "Exam.h"
#include <iostream>

using namespace std;

const int LENGTH_OF_STUDENT_NAME = 255;

Exam::Exam()
{
	m_studentName = new char[LENGTH_OF_STUDENT_NAME]{};
	strcpy_s(m_studentName, LENGTH_OF_STUDENT_NAME, "Isaac");
	m_date = 10100;
	m_mark = 1;
}

Exam::Exam(const char* studentName, const int date, const int mark)
{
	m_studentName = new char[LENGTH_OF_STUDENT_NAME]{};
	strcpy_s(m_studentName, LENGTH_OF_STUDENT_NAME, studentName);
	m_date = date;
	m_mark = mark;
}

Exam::Exam(const Exam & exam)
{
	m_studentName = new char[LENGTH_OF_STUDENT_NAME]{};
	strcpy_s(m_studentName, LENGTH_OF_STUDENT_NAME, exam.m_studentName);
	m_date = exam.m_date;
	m_mark = exam.m_mark;
}

Exam::~Exam() { delete[] m_studentName; }

char* Exam::GetStudentName() { return m_studentName; }
int Exam::GetDate() { return m_date; }
int Exam::GetMark() { return m_mark; }

int Exam::SetStudentName(char* studentName)
{
	if (strlen(studentName) < LENGTH_OF_STUDENT_NAME)
	{
		strcpy_s(m_studentName, LENGTH_OF_STUDENT_NAME, studentName);
		return 0;
	}
	else
	{
		return -1;
	}
}

int Exam::SetDate(int date) 
{
	if (date < 0)
	{
		return -1;
	}
	else
	{
		int day = date / 10000;
		int month = (date % 10000) / 100;
		if (day >= 1 && day <= 31 && month >= 1 && month <= 12)
		{
			m_date = date;
			return 0;
		}
		else
		{
			return -1;
		}
	}
}

int Exam::SetMark(int mark)
{
	if (mark >= 1 && mark <= 5)
	{
		m_mark = mark;
		return 0;
	}
	else
	{
		return -1;
	}
}

void Exam::Print() const
{
	cout << "Student name: " << m_studentName << '\n';
	cout << "Date: " << m_date << '\n';
	cout << "Mark: " << m_mark << '\n';
	cout << '\n';
}

bool operator<(const Exam& exam1, const Exam& exam2) { return exam1.m_mark < exam2.m_mark; }
bool operator>(const Exam& exam1, const Exam& exam2) { return exam1.m_mark > exam2.m_mark; }

Exam& Exam::operator=(const Exam& exam)
{
	if (this == &exam)
	{
		return *this;
	}
	else
	{
		strcpy_s(m_studentName, LENGTH_OF_STUDENT_NAME, exam.m_studentName);
		m_date = exam.m_date;
		m_mark = exam.m_mark;
		return *this;
	}
}