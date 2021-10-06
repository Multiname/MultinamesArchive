#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>
#include <iostream>

class Animal
{
public:
	Animal(std::string name, int color, std::string type_voice);
	~Animal();

	virtual void outName() = 0;
	virtual void outColor() = 0;
	virtual void turnVoice() = 0;

protected:
	std::string m_name{};
	int m_color{};
	std::string m_type_voice{};

};

#endif // !ANIMAL_H

void Animal::turnVoice()
{
	std::cout << m_type_voice << '\n';
}