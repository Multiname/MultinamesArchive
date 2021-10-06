#ifndef DOG_H
#define DOG_H
#include"Animal.h"
#include <iostream>

class Dog : public Animal
{
	Dog(std::string name, int color, std::string type_voice) : Animal(name, color, type_voice) {};


	void outName() override
	{
		std::cout << m_name << '\n';
	}
};

#endif // !DOG_H