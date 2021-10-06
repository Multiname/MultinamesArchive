#include "Fourangle.h"
#include <math.h>
#include <stdexcept>
#include <iostream>

using namespace std;

Fourangle::Fourangle() { m_points = nullptr; }
Fourangle::Fourangle(char* name, double** points) : Shape(name)
{
	m_points = new double* [4]{};
	m_points[0] = new double[2]{};
	m_points[1] = new double[2]{};
	m_points[2] = new double[2]{};
	m_points[3] = new double[2]{};

	try
	{
		m_points[0][0] = points[0][0];
		m_points[0][1] = points[0][1];
		m_points[1][0] = points[1][0];
		m_points[1][1] = points[1][1];
		m_points[2][0] = points[2][0];
		m_points[2][1] = points[2][1];
		m_points[3][0] = points[3][0];
		m_points[3][1] = points[3][1];
	}
	catch (const out_of_range& e)
	{
		cout << "Error: " << e.what() << "\n";
	}
}

Fourangle::~Fourangle()
{
	delete[] m_points[0];
	delete[] m_points[1];
	delete[] m_points[2];
	delete[] m_points[3];
	delete[] m_points;
}

void Fourangle::SetPoints(double** points)
{
	try
	{
		m_points[0][0] = points[0][0];
		m_points[0][1] = points[0][1];
		m_points[1][0] = points[1][0];
		m_points[1][1] = points[1][1];
		m_points[2][0] = points[2][0];
		m_points[2][1] = points[2][1];
		m_points[3][0] = points[3][0];
		m_points[3][1] = points[3][1];
	}
	catch (const out_of_range& e)
	{
		cout << "Error: " << e.what() << "\n";
	}
}

double** Fourangle::GetPoints() { return m_points; }

double Fourangle::CalculatePerimeter()
{
	return sqrt(pow(m_points[0][0] - m_points[1][0], 2) + pow(m_points[0][1] - m_points[1][1], 2)) +
		sqrt(pow(m_points[1][0] - m_points[2][0], 2) + pow(m_points[1][1] - m_points[2][1], 2)) +
		sqrt(pow(m_points[2][0] - m_points[3][0], 2) + pow(m_points[2][1] - m_points[3][1], 2)) +
		sqrt(pow(m_points[3][0] - m_points[0][0], 2) + pow(m_points[3][1] - m_points[0][1], 2));
}