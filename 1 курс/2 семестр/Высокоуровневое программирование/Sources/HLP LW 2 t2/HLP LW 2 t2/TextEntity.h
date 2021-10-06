#ifndef TEXT_ENTITY_H
#define TEXT_ENTITY_H
#include "Entity.h"
#include <string>

namespace KMK
{
	class TextEntity : public Entity
	{
	public:
		TextEntity(Id id, Date date, std::string content, Id ownerId);
		TextEntity(TextEntity* textEntity);
		virtual ~TextEntity() {}

		std::string GetContent();
		Id GetOwnerId();

		void SetContent(std::string content);
		void SetOwnerId(Id ownerId);

	private:
		std::string m_content{};
		Id m_ownerId{};
	};
}

#endif // !TEXT_ENTITY_H