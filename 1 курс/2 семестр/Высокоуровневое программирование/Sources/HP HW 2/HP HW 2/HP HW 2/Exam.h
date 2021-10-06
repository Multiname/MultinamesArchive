#ifndef EXAM_H
#define EXAM_H

class Exam
{
	char* m_studentName{};
	int m_date{};
	int m_mark{};

public:
	Exam();
	Exam(const char* studentName, const int date, const int mark);
	Exam(const Exam & exam);
	~Exam();

	char* GetStudentName();
	int GetDate();
	int GetMark();

	int SetStudentName(char* studentName);
	int SetDate(int date);
	int SetMark(int mark);

	void Print() const;

	friend bool operator<(const Exam& exam1, const Exam& exam2);
	friend bool operator>(const Exam& exam1, const Exam& exam2);
	Exam& operator=(const Exam& exam1);
};

#endif