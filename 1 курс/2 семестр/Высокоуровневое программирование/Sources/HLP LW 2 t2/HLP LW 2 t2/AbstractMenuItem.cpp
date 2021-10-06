#include "AbstractMenuItem.h"
#include <iostream>

using namespace KMK;

MenuItem::MenuItem(std::string itemName)
{
	m_itemName = itemName;
}

std::string MenuItem::GetItemName()
{
	return m_itemName;
}

void MenuItem::PrintItemName()
{
	std::cout << m_itemName;
}