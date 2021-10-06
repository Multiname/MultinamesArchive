#pragma once
#include "Shape.h"

using namespace std;

class Fourangle :public Shape
{
public:
	Fourangle();
	Fourangle(char* name, double** points);
	~Fourangle();

	void SetPoints(double** points);
	double** GetPoints();

	double CalculatePerimeter();

private:
	double** m_points{};
};