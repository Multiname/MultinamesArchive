#include "Sort.h"
#include <iostream>

namespace KMK
{
	void JustSwap(Entity*& firstEntity, Entity*& secondEntity)
	{
		Entity* temp = firstEntity;
		firstEntity = secondEntity;
		secondEntity = temp;
	}

	void Swap(Entity*& firstEntity, Entity*& secondEntity, OrderMode order, FieldMode mode)
	{
		if (mode == FieldMode::ID || mode == FieldMode::OWNER_ID || mode == FieldMode::ADRESSEE_ID)
		{
			if (order == OrderMode::DESCENDING && GetIdField(firstEntity, mode) < GetIdField(secondEntity, mode) ||
				order == OrderMode::ASCENDING && GetIdField(firstEntity, mode) > GetIdField(secondEntity, mode))
			{
				JustSwap(firstEntity, secondEntity);
			}
		}
		else if (mode == FieldMode::CONTENT || mode == FieldMode::NAME || mode == FieldMode::LOGIN || mode == FieldMode::PASSWORD)
		{
			Iteration letter = 0;
			while (GetTextField(firstEntity, mode)[letter] == GetTextField(secondEntity, mode)[letter] &&
				letter < GetTextField(firstEntity, mode).length() - 1 && letter < GetTextField(secondEntity, mode).length() - 1)
			{
				++letter;
			}

			if (order == OrderMode::DESCENDING && GetTextField(firstEntity, mode)[letter] < GetTextField(secondEntity, mode)[letter] ||
				order == OrderMode::ASCENDING && GetTextField(firstEntity, mode)[letter] > GetTextField(secondEntity, mode)[letter])
			{
				JustSwap(firstEntity, secondEntity);
			}
		}
		else if (mode == FieldMode::DATE || mode == FieldMode::REMINDER_TIME)
		{
			if (order == OrderMode::DESCENDING &&
				(GetDateField(firstEntity, mode).year < GetDateField(secondEntity, mode).year ||
					GetDateField(firstEntity, mode).year == GetDateField(secondEntity, mode).year &&
					(GetDateField(firstEntity, mode).month < GetDateField(secondEntity, mode).month ||
						GetDateField(firstEntity, mode).month == GetDateField(secondEntity, mode).month &&
						GetDateField(firstEntity, mode).day < GetDateField(secondEntity, mode).day)) ||
				order == OrderMode::ASCENDING &&
				(GetDateField(firstEntity, mode).year > GetDateField(secondEntity, mode).year ||
					GetDateField(firstEntity, mode).year == GetDateField(secondEntity, mode).year &&
					(GetDateField(firstEntity, mode).month > GetDateField(secondEntity, mode).month ||
						GetDateField(firstEntity, mode).month == GetDateField(secondEntity, mode).month &&
						GetDateField(firstEntity, mode).day > GetDateField(secondEntity, mode).day)))
			{
				JustSwap(firstEntity, secondEntity);
			}
		}
	}

	void Sort(Entity**& entities, size_t size, OrderMode order, FieldMode mode)
	{
		if (size > 1)
		{
			short bottomBorder = 0;
			short upperBorder = size - 1;
			while (upperBorder - bottomBorder > 0)
			{
				for (Iteration i = bottomBorder; i < upperBorder; ++i)
				{
					Swap(entities[i], entities[i + 1], order, mode);
				}
				--upperBorder;

				for (Iteration i = upperBorder; i > bottomBorder; --i)
				{
					Swap(entities[i - 1], entities[i], order, mode);
				}
				++bottomBorder;
			}
		}
	}
}