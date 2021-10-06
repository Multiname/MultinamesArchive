#include "TextEntity.h"
#include <iostream>

using namespace KMK;

TextEntity::TextEntity(Id id, Date date, std::string content, Id ownerId) : Entity(id, date)
{
	m_content = content;
	m_ownerId = ownerId;

}

TextEntity::TextEntity(TextEntity* textEntity) : Entity(textEntity->GetId(), textEntity->GetDate())
{
	m_content = textEntity->m_content;
	m_ownerId = textEntity->m_ownerId;
}

std::string TextEntity::GetContent() { return m_content; }
Id TextEntity::GetOwnerId() { return m_ownerId; }

void TextEntity::SetContent(std::string content) { m_content = content; }
void TextEntity::SetOwnerId(Id ownerId) { m_ownerId = ownerId; }