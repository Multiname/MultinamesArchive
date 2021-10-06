#pragma once

class Shape
{
public:
	Shape();
	Shape(char* name);
	~Shape();

	void SetName(char* name);
	char* GetName();

	virtual double CalculatePerimeter() = 0;

private:
	char* m_name{};
};