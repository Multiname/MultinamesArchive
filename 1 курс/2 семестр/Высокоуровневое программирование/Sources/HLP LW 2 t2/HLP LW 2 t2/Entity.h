#ifndef ENTITY_H
#define ENTITY_H
#include "TypeDefinitions.h"

namespace KMK
{
	class Entity
	{
	public:
		struct Date
		{
			unsigned short day{};
			unsigned short month{};
			unsigned short year{};
		};

		Entity(Id id, Date date);
		Entity(Entity* entity);
		virtual ~Entity() {}

		Id GetId();
		Date GetDate();

		void SetId(Id id);
		void SetDate(Date date);

	private:
		Id m_id{};
		Date m_date{};
	};
}

#endif // !ENTITY_H