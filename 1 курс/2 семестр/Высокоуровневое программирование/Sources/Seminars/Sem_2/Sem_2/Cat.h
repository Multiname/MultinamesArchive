#ifndef CAT_H
#define CAT_H
#include "Animal.h"

class Cat : public Animal
{
	Cat(std::string name, int color, std::string type_voice) :
		m_name(name), m_color(color), m_type_voice(type_voice) {};
	void Meow():
	{
		void turnVoice()
		{
			Animal::turnVoice();
		}
	}
};

#endif // !CAT_H