#ifndef USER_ITEM_H
#define USER_ITEM_H
#include "ItemWIthMenu.h"

namespace KMK
{
	class UserItem : public ItemWithMenu
	{
	public:
		UserItem(char* itemName, char* tempDataBase, char* Id);

		int Run();
	private:
		char* m_tempDataBase = nullptr;
		char* m_id{};
	};
}

#endif // !USER_ITEM_H