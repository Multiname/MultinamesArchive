#include "Edit.h"
#include "Dialogue.h"
#include "Interest.h"
#include "Reminder.h"
#include "Theme.h"
#include "User.h"

namespace KMK
{
	void Edit(Entity**& entities, size_t size, Id idToEdit, void* newField, FieldMode mode)
	{
		unsigned short themeNumber = 0;
		while (themeNumber < size)
		{
			if (entities[themeNumber]->GetId() != idToEdit)
			{
				++themeNumber;
			}
			else
			{
				break;
			}
		}

		if (themeNumber < size)
		{
			if (mode == FieldMode::ID)
			{
				entities[themeNumber]->SetId(*(Id*)newField);
			}
			else if (mode == FieldMode::DATE)
			{
				entities[themeNumber]->SetDate(*(Entity::Date*)newField);
			}
			else if (mode == FieldMode::CONTENT)
			{
				dynamic_cast<TextEntity*>(entities[themeNumber])->SetContent(*(std::string*)newField);
			}
			else if (mode == FieldMode::OWNER_ID)
			{
				dynamic_cast<TextEntity*>(entities[themeNumber])->SetOwnerId(*(Id*)newField);
			}
			else if (mode == FieldMode::ADRESSEE_ID)
			{
				dynamic_cast<Dialogue*>(entities[themeNumber])->SetAdresseeId(*(Id*)newField);
			}
			else if (mode == FieldMode::REMINDER_TIME)
			{
				dynamic_cast<Reminder*>(entities[themeNumber])->SetReminderTime(*(Entity::Date*)newField);
			}
			else if (mode == FieldMode::NAME)
			{
				dynamic_cast<User*>(entities[themeNumber])->SetName(*(std::string*)newField);
			}
			else if (mode == FieldMode::LOGIN)
			{
				dynamic_cast<User*>(entities[themeNumber])->SetLogin(*(std::string*)newField);
			}
			else if (mode == FieldMode::PASSWORD)
			{
				dynamic_cast<User*>(entities[themeNumber])->SetPassword(*(std::string*)newField);
			}
		}
	}
}