#include <iostream>
#include "Vector.h"

void main()
{
	Vector vector = Vector();
	std::cout << vector.CheckEmpty() << '\n';
	vector.AddToEnd(1);
	vector.AddToEnd(2);
	vector.AddToEnd(3);
	std::cout << vector.CheckEmpty() << '\n';
	std::cout << vector.GetElement(1) << '\n';
	std::cout << vector.GetSize() << '\n';
	vector.DeleteLast();
	std::cout << vector.GetSize() << '\n';
	vector.SetElement(1, 5);
	std::cout << vector.GetElement(1) << '\n';
	vector.DeleteAll();
	std::cout << vector.GetSize() << '\n';
}