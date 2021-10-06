#ifndef ITEM_WITH_MENU_H
#define ITEM_WITH_MENU_H
#include "AbstractMenuItem.h"

namespace KMK
{
	class ItemWithMenu : public MenuItem
	{
	public:
		ItemWithMenu(char* itemName, MenuItem** items, size_t count);

		void SetItems(MenuItem** items);
		void SetCount(size_t count);

		int Run();

	private:
		MenuItem** m_items = nullptr;
		size_t m_count{};
	};
}

#endif // !ITEM_WITH_MENU_H