#include <iostream>
#include <math.h>
#include <stdexcept>

using namespace std;

class Shape
{
private:
	char* m_name{};
public:
	Shape() { m_name = nullptr; }
	Shape(char* name)
	{
		m_name = new char[256]{};
		strcpy_s(m_name, 256, name);
	}
	~Shape() { delete[] m_name; }

	void SetName(char* name) { strcpy_s(m_name, 256, name); }
	char* GetName() { return m_name; }

	virtual double CalculatePerimeter() = 0;
};

class Triangle : public Shape
{
private:
	double* m_pointA{};
	double* m_pointB{};
	double* m_pointC{};
public:
	Triangle()
	{
		m_pointA = nullptr;
		m_pointB = nullptr;
		m_pointC = nullptr;
	}
	Triangle(char* name, double* pointA, double* pointB, double* pointC) : Shape(name)
	{
		cout << pointA << " " << *pointA << "\n";

		m_pointA = new double[2];
		m_pointB = new double[2];
		m_pointC = new double[2];

		try
		{
			m_pointA[0] = pointA[0];
			m_pointA[1] = pointA[1];
			m_pointB[0] = pointB[0];
			m_pointB[1] = pointB[1];
			m_pointC[0] = pointC[0];
			m_pointC[1] = pointC[1];
		}
		catch (const out_of_range& e)
		{
			cout << "Error: " << e.what() << "\n";
		}
	}
	~Triangle()
	{
		delete[] m_pointA;
		delete[] m_pointB;
		delete[] m_pointC;
	}

	void SetPoints(double* pointA, double* pointB, double* pointC)
	{
		try
		{
			m_pointA[0] = pointA[0];
			m_pointA[1] = pointA[1];
			m_pointB[0] = pointB[0];
			m_pointB[1] = pointB[1];
			m_pointC[0] = pointC[0];
			m_pointC[1] = pointC[1];
		}
		catch (const out_of_range& e)
		{
			cout << "Error: " << e.what() << "\n";
		}
	}
	double* GetPointA() { return m_pointA; }
	double* GetPointB() { return m_pointB; }
	double* GetPointC() { return m_pointC; }

	double CalculatePerimeter()
	{
		return sqrt(pow(m_pointA[0] - m_pointB[0], 2) + pow(m_pointA[1] - m_pointB[1], 2)) +
			sqrt(pow(m_pointB[0] - m_pointC[0], 2) + pow(m_pointB[1] - m_pointC[1], 2)) +
			sqrt(pow(m_pointC[0] - m_pointA[0], 2) + pow(m_pointC[1] - m_pointA[1], 2));
	}
};

class Test
{
public:
	Test(double* test)
	{
		m_test = new double[2]{};
		m_test[0] = test[0];
		m_test[1] = test[1];
	}

	void Print()
	{
		cout << m_test[0] << " " << m_test[1] << "\n";
	}

private:
	double* m_test{};
};

int main()
{
	char* name = new char[4]{ "ABC" };
	double* A = new double[2]{ 5, 0 };
	double* B = new double[2]{ 3, 0 };
	double* C = new double[2]{ 0, 3 };
	cout << A << " " << *A << "\n";
	Triangle triangle(name, A, B, C);

	//Test test(A);
	//test.Print();

	return 0;
}