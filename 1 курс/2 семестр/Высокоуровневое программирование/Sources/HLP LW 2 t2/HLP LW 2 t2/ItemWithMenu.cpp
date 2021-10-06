#include "ItemWIthMenu.h"
#include <iostream>
#include "TypeDefinitions.h"

using namespace KMK;

ItemWithMenu::ItemWithMenu(char* itemName, MenuItem** items, size_t count) : MenuItem(itemName)
{
	m_items = items;
	m_count = count;
}

void ItemWithMenu::SetItems(MenuItem** items)
{
	m_items = items;
}

void ItemWithMenu::SetCount(size_t count)
{
	m_count = count;
}

int ItemWithMenu::Run()
{
	for (Iteration i = 0; i < m_count; i++)
	{
		std::cout << i << ". ";
		m_items[i]->GetItemName();
		std::cout << '\n';
	}
	std::cout << "Enter command: ";
	short command;
	std::cin >> command;
	return m_items[command]->Run();
}