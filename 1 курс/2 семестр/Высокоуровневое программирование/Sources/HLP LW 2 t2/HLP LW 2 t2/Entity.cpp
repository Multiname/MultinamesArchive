#include "Entity.h"

using namespace KMK;

Entity::Entity(Id id, Date date)
{
	m_id = id;
	m_date = date;
}

Entity::Entity(Entity* entity)
{
	m_id = entity->m_id;
	m_date = entity->m_date;
}

Id Entity::GetId() { return m_id; }
Entity::Date Entity::GetDate() { return m_date; }

void Entity::SetId(Id id) { m_id = id; }
void Entity::SetDate(Date date)
{
	m_date.day = date.day;
	m_date.month = date.month;
	m_date.year= date.year;
}