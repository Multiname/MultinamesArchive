#include "ItemWithMenu.h"
#include <iostream>

using namespace KMK;

ItemWithMenu::ItemWithMenu(char* item_name, ItemMenu* items, size_t numberOfItems, Func func) : ItemMenu(item_name, func)
{
	m_items = items;
	m_numberOfItems = numberOfItems;
}

char* ItemWithMenu::GetItemName()
{
	return ItemMenu::GetItemName();
}

ItemMenu* ItemWithMenu::GetItems()
{
	return m_items;
}

size_t ItemWithMenu::GetNumberOfItems()
{
	return m_numberOfItems;
}

void  ItemWithMenu::PrintItemName()
{
	ItemMenu::PrintItemName();
}

int  ItemWithMenu::run()
{
	for (int i = 0; i < m_numberOfItems; i++)
	{
		std::cout << i << ". ";
		m_items[i].PrintItemName();
		std::cout << '\n';
	}

	std::cout << "Enter command: ";
	int command;
	std::cin >> command;
	m_items[command].run();

	return 0;
}