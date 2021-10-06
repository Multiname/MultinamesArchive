//#include "Add.h"
//#include "Dialogue.h"
//#include "Interest.h"
//#include "Reminder.h"
//#include "Theme.h"
//#include "User.h"
//
//namespace KMK
//{
//	void Add(Entity**& entities, size_t& size, Entity* newElement)
//	{
//		Entity** temp = new Entity * [size + 1]{};
//
//		for (Iteration i{}; i < size; ++i)
//		{
//			if (dynamic_cast<Dialogue*>(entities[i]))
//			{
//				temp[i] = new Dialogue{ dynamic_cast<Dialogue*>(entities[i]) };
//			}
//			else if (dynamic_cast<Interest*>(entities[i]))
//			{
//				temp[i] = new Interest{ dynamic_cast<Interest*>(entities[i]) };
//			}
//			else if (dynamic_cast<Reminder*>(entities[i]))
//			{
//				temp[i] = new Reminder{ dynamic_cast<Reminder*>(entities[i]) };
//			}
//			else if (dynamic_cast<Theme*>(entities[i]))
//			{
//				temp[i] = new Theme{ dynamic_cast<Theme*>(entities[i]) };
//			}
//			else if (dynamic_cast<User*>(entities[i]))
//			{
//				temp[i] = new User{ dynamic_cast<User*>(entities[i]) };
//			}
//		}
//
//		temp[size] = newElement;
//
//		for (Iteration i{}; i < size; ++i)
//		{
//			delete entities[i];
//		}
//		delete[] entities;
//		entities = temp;
//		++size;
//	}
//}