#pragma once
#include "Shape.h"

using namespace std;

class Triangle : public Shape
{
public:
	Triangle();
	Triangle(char* name, double* pointA, double* pointB, double* pointC);
	~Triangle();
	
	void SetPoints(double* pointA, double* pointB, double* pointC);
	double* GetPointA();
	double* GetPointB();
	double* GetPointC();

	double CalculatePerimeter();
	
private:
	double* m_pointA {};
	double* m_pointB {};
	double* m_pointC {};
};