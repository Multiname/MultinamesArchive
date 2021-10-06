#include "Remove.h"
#include "Dialogue.h"
#include "Interest.h"
#include "Reminder.h"
#include "Theme.h"
#include "User.h"

using namespace KMK;

void KMK::Remove(Entity**& entites, size_t& size, Id idToRemove)
{
	bool found = false;
	for (Iteration i{}; i < size; ++i)
	{
		if (idToRemove == entites[i]->GetId())
		{
			found = true;
			break;
		}
	}

	if (found == true)
	{
		Entity** temp = new Entity * [size - 1]{};
		unsigned short tempElementNumber = 0;
		for (Iteration i{}; i < size; ++i)
		{
			if (entites[i]->GetId() != idToRemove)
			{
				if (dynamic_cast<Dialogue*>(entites[i]))
				{
					temp[tempElementNumber] = new Dialogue{ dynamic_cast<Dialogue*>(entites[i]) };
				}
				else if (dynamic_cast<Interest*>(entites[i]))
				{
					temp[tempElementNumber] = new Interest{ dynamic_cast<Interest*>(entites[i]) };
				}
				else if (dynamic_cast<Reminder*>(entites[i]))
				{
					temp[tempElementNumber] = new Reminder{ dynamic_cast<Reminder*>(entites[i]) };
				}
				else if (dynamic_cast<Theme*>(entites[i]))
				{
					temp[tempElementNumber] = new Theme{ dynamic_cast<Theme*>(entites[i]) };
				}
				else if (dynamic_cast<User*>(entites[i]))
				{
					temp[tempElementNumber] = new User{ dynamic_cast<User*>(entites[i]) };
				}
				++tempElementNumber;
			}
		}

		for (Iteration i{}; i < size; ++i)
		{
			delete entites[i];
		}
		delete[] entites;
		entites = temp;
		--size;
	}
}