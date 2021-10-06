#ifndef ITEM_WITH_MENU_H
#define ITEM_WITH_MENU_H
#include "AbstractItemMenu.h"

namespace KMK
{
	class ItemWithMenu : public ItemMenu
	{
	public:
		ItemWithMenu(char* item_name, ItemMenu* items, size_t numberOfItems, Func func);

		char* GetItemName();
		ItemMenu* GetItems();
		size_t GetNumberOfItems();

		void PrintItemName();
		int run();
	private:
		ItemMenu* m_items;
		size_t m_numberOfItems;
	};
}

#endif // !ITEM_WITH_MENU_H
