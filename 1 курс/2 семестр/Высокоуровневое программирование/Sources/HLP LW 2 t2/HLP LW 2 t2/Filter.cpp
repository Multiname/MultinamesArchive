#include "Filter.h"
#include "Constants.h"
#include <cmath>
#include "Dialogue.h"
#include "Interest.h"
#include "Reminder.h"
#include "Theme.h"
#include "User.h"

namespace KMK
{
	void CreateNewList(Entity**& entities, size_t& size, bool* indexes, size_t newSize)
	{
		Entity** filteredEntities = new Entity * [newSize] {};
		Iteration numberOfEntity = 0;
		for (Iteration i{}; i < size; ++i)
		{
			if (indexes[i] == true)
			{
				if (dynamic_cast<Dialogue*>(entities[i]))
				{
					filteredEntities[numberOfEntity] = new Dialogue{ dynamic_cast<Dialogue*>(entities[i]) };
				}
				else if (dynamic_cast<Interest*>(entities[i]))
				{
					filteredEntities[numberOfEntity] = new Interest{ dynamic_cast<Interest*>(entities[i]) };
				}
				else if (dynamic_cast<Reminder*>(entities[i]))
				{
					filteredEntities[numberOfEntity] = new Reminder{ dynamic_cast<Reminder*>(entities[i]) };
				}
				else if (dynamic_cast<Theme*>(entities[i]))
				{
					filteredEntities[numberOfEntity] = new Theme{ dynamic_cast<Theme*>(entities[i]) };
				}
				else if (dynamic_cast<User*>(entities[i]))
				{
					filteredEntities[numberOfEntity] = new User{ dynamic_cast<User*>(entities[i]) };
				}
				++numberOfEntity;
			}
			delete entities[i];
		}
		delete[] entities;
		entities = filteredEntities;
		size = newSize;
	}

	void Filter(Entity**& entities, size_t& size, Id fieldForSearch, FieldMode mode)
	{
		unsigned long int tens = 10;
		unsigned short numberOfDigits = 1;
		while (fieldForSearch / tens != 0)
		{
			tens *= 10;
			++numberOfDigits;
		}

		bool* indexes = new bool[size] {};
		size_t newSize = 0;
		for (Iteration i{}; i < MAXIMUM_NUMBER_OF_DIGITS_IN_ID - numberOfDigits + 1; ++i)
		{
			for (Iteration j{}; j < size; j++)
			{
				if (fieldForSearch == (GetIdField(entities[j], mode) / (int)pow(10, i)) % tens)
				{
					if (indexes[j] != true)
					{
						indexes[j] = true;
						++newSize;
					}
				}
			}
		}

		CreateNewList(entities, size, indexes, newSize);
	}

	void Filter(Entity**& entities, size_t& size, std::string fieldForSearch, FieldMode mode)
	{
		long long fieldForSearchLength = fieldForSearch.length();

		bool* indexes = new bool[size] {};
		int newSize = 0;
		for (Iteration i{}; i < size; ++i)
		{
			for (long long j{}; j < (long long)GetTextField(entities[i], mode).length() - fieldForSearchLength + 1; ++j)
			{
				std::string temp{};
				for (Iteration k{}; k < fieldForSearchLength; ++k)
				{
					temp += GetTextField(entities[i], mode)[j + k];
				}
				if (temp == fieldForSearch)
				{
					indexes[i] = true;
					++newSize;
					break;
				}
			}
		}

		CreateNewList(entities, size, indexes, newSize);
	}

	void Filter(Entity**& entities, size_t& size, Entity::Date fieldForSearch, FieldMode mode)
	{
		bool* indexes = new bool[size] {};
		unsigned short newSize = 0;
		for (Iteration i{}; i < size; ++i)
		{
			if ((GetDateField(entities[i], mode).day == fieldForSearch.day || fieldForSearch.day == 0) &&
				(GetDateField(entities[i], mode).month == fieldForSearch.month || fieldForSearch.month == 0) &&
				(GetDateField(entities[i], mode).year == fieldForSearch.year || fieldForSearch.year == 0))
			{
				indexes[i] = true;
				++newSize;
			}
		}

		CreateNewList(entities, size, indexes, newSize);
	}
}