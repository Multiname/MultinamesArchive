#ifndef GET_FIELD_H
#define GET_FIELD_H
#include "Entity.h"
#include <string>

namespace KMK
{
	enum class FieldMode
	{
		ID,
		DATE,
		CONTENT,
		OWNER_ID,
		ADRESSEE_ID,
		REMINDER_TIME,
		NAME,
		LOGIN,
		PASSWORD
	};

	Id GetIdField(Entity* entity, FieldMode mode);
	std::string GetTextField(Entity* entity, FieldMode mode);
	Entity::Date GetDateField(Entity* entity, FieldMode mode);
}

#endif // !GET_FIELD_H