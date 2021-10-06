#ifndef ENTITY_LIST_ITEM_H
#define ENTITY_LIST_ITEM_H
#include "AbstractMenuItem.h"
#include "IdCounter.h"
#include "Entity.h"

namespace KMK
{
	class EntityListItem : public MenuItem
	{
	public:
		enum EntityMode
		{
			DIALOGUE,
			INTEREST,
			REMINDER,
			THEME,
			USER
		};

		EntityListItem(EntityMode entityMode, char* itemName, char* entityDatabase, char* idCounterDatabase);

		int Run();

	private:
		EntityMode m_entityMode{};
		char* m_entityDatabase = nullptr;
		char* m_idCounterDatabase = nullptr;
		size_t m_size{};
		Entity** m_entityList = nullptr;
		IdCounter m_idCounter{};

		bool IsTextEntity();
		void Draw();
		void ReadFile();

		enum  Command
		{
			RESET,
			ADD,
			REMOVE,
			EDIT,
			SORT,
			FILTER,
			ID,
			EXIT
		};
	};
}

#endif // !ENTITY_LIST_ITEM_H
