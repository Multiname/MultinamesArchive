#include "AbstractItemMenu.h"
#include <iostream>

using namespace KMK;

const int KMK::LENGTH_OF_FIELD = 255;

ItemMenu::ItemMenu(char* item_name, Func func)
{
	m_item_name = new char[LENGTH_OF_FIELD];
	strcpy_s(m_item_name, LENGTH_OF_FIELD, item_name);
	m_func = func;
}

char* ItemMenu::GetItemName()
{
	return m_item_name;
}

void ItemMenu::PrintItemName()
{
	std::cout << m_item_name;
}

int ItemMenu::run()
{
	return (*m_func)();
}