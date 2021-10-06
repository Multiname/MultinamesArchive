#include "Shape.h"
#include <iostream>

using namespace std;

Shape::Shape() { m_name = nullptr; }
Shape::Shape(char* name)
{
	m_name = new char[strlen(name) + 1]{};
	strcpy_s(m_name, 256, name);
}

Shape::~Shape() { delete[] m_name; }

void Shape::SetName(char* name) { strcpy_s(m_name, 256, name); }
char* Shape::GetName() { return m_name; }