#include "Triangle.h"
#include <math.h>
#include <stdexcept>
#include <iostream>

using namespace std;

Triangle::Triangle()
{
	m_pointA = nullptr;
	m_pointB = nullptr;
	m_pointC = nullptr;
}

Triangle::Triangle(char* name, double* pointA, double* pointB, double* pointC) : Shape(name)
{
	//m_pointA = new double[2]{};
	//m_pointB = new double[2]{};
	//m_pointC = new double[2]{};

	//try
	//{
	//	m_pointA[0] = pointA[0];
	//	m_pointA[1] = pointA[1];
	//	m_pointB[0] = pointB[0];
	//	m_pointB[1] = pointB[1];
	//	m_pointC[0] = pointC[0];
	//	m_pointC[1] = pointC[1];
	//}
	//catch (const out_of_range& e)
	//{
	//	cout << "Error: " << e.what() << "\n";
	//}
}

Triangle::~Triangle()
{
	//delete[] m_pointA;
	//	delete[] m_pointB;
	//	delete[] m_pointC;
}

void Triangle::SetPoints(double* pointA, double* pointB, double* pointC)
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

double* Triangle::GetPointA() { return m_pointA; }
double* Triangle::GetPointB() { return m_pointB; }
double* Triangle::GetPointC() { return m_pointC; }

double Triangle::CalculatePerimeter()
{
	return sqrt(pow(m_pointA[0] - m_pointB[0], 2) + pow(m_pointA[1] - m_pointB[1], 2)) +
		sqrt(pow(m_pointB[0] - m_pointC[0], 2) + pow(m_pointB[1] - m_pointC[1], 2)) +
		sqrt(pow(m_pointC[0] - m_pointA[0], 2) + pow(m_pointC[1] - m_pointA[1], 2));
}