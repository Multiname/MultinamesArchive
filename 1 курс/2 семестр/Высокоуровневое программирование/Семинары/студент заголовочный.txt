#ifndef STUDENT_H

#define STUDENT_H

class Student
{
	char* m_firstName{};
	char* m_secondName{};
	int* m_marks{};
	int m_numberOfMarks{};

public:
	Student();
	Student(char* firstName, char* secondName, int* marks, int numberOfMarks);
	Student(Student * student);
	~Student();

	void SetFirstName(char* firstName);
	void SetSecondName(char* secondName);
	int SetMarks(int* marks);
	void SetNumberOfMarks(int numberOfMarks);

	char* GetFirstName();
	char* GetSecondName();
	int* GetMarks();
	int GetNumberOfMarks();

	float GetAverageMark();

	void PrintInfo();
};

#endif
