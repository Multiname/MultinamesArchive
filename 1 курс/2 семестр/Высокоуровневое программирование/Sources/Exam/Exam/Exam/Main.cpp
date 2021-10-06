#include <iostream>
#include <string>
#include "Triangle.h"
#include "Fourangle.h"

using namespace std;

class Example;

void PrintName(Example* example);

class Example
{
public:
	Example(string name) : m_name(name){}

	void Function()
	{
		cout << "Some code\n";
	}

	string GetName() { return m_name; }
	void SayName() { PrintName(this); }

private:
	string m_name{};
};

void PrintName(Example* example)
{
	cout << example->GetName() << "\n";
}

int main()
{
	//Example* example = new Example("Mike");
	//example->Function();
	//example->SayName();

	double* A = new double{ 2 };
	double* B = new double{ 3 };
	double* C = new double{ 5 };
	char* triangleName = new char[4] {"ABC"};

	Triangle triangle{ triangleName, A, B, C };

	//cout << "Perimeter of " << triangle.GetName() << " is "
	//	<< triangle.CalculatePerimeter() << "\n";

	//delete[] A;
	//delete[] B;
	//delete[] C;
	//delete[] triangleName;

	return 0;
}