#include "GetField.h"
#include "Dialogue.h"
#include "User.h"
#include "Reminder.h"

namespace KMK
{
	Id GetIdField(Entity* entity, FieldMode mode)
	{
		if (mode == FieldMode::ID)
		{
			return entity->GetId();
		}
		else if (mode == FieldMode::OWNER_ID)
		{
			return dynamic_cast<TextEntity*>(entity)->GetOwnerId();
		}
		else if (mode == FieldMode::ADRESSEE_ID)
		{
			return dynamic_cast<Dialogue*>(entity)->GetAdresseeId();
		}
	}

	std::string GetTextField(Entity* entity, FieldMode mode)
	{
		if (mode == FieldMode::CONTENT)
		{
			return dynamic_cast<TextEntity*>(entity)->GetContent();
		}
		else if (mode == FieldMode::NAME)
		{
			return dynamic_cast<User*>(entity)->GetName();
		}
		else if (mode == FieldMode::LOGIN)
		{
			return dynamic_cast<User*>(entity)->GetLogin();
		}
		else if (mode == FieldMode::PASSWORD)
		{
			return dynamic_cast<User*>(entity)->GetPassword();
		}
	}

	Entity::Date GetDateField(Entity* entity, FieldMode mode)
	{
		if (mode == FieldMode::DATE)
		{
			return entity->GetDate();
		}
		else if (mode == FieldMode::REMINDER_TIME)
		{
			return dynamic_cast<Reminder*>(entity)->GetReminderTime();
		}
	}
}