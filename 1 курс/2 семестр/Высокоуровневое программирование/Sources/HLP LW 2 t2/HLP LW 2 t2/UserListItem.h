#ifndef USER_LIST_ITEM_H
#define USER_LIST_ITEM_H
#include "AbstractMenuItem.h"
#include "User.h"
#include "Storage.h"

namespace KMK
{
	class UserListItem : public MenuItem
	{
	public:
		UserListItem(std::string itemName, Storage* storage);

		int Run();

	private:
		Storage* m_storage{};
	};
}

#endif // !USER_LIST_ITEM_H