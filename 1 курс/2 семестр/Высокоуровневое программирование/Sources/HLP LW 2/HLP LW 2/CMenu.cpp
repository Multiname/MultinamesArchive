#include "CMenu.h"
#include <iostream>

using namespace KMK;

CMenu::CMenu(char* title, ItemMenu* items, size_t count)
{
	m_title = new char[LENGTH_OF_FIELD];
	strcpy_s(m_title, LENGTH_OF_FIELD, title);
	m_items = items;
	m_count = count;
}

int CMenu::GetSelect()
{
	return m_select;
}

bool CMenu::GetRunning()
{
	return m_running;
}

char* CMenu::GetTitle()
{
	return m_title;
}

size_t CMenu::GetCount()
{
	return m_count;
}

ItemMenu* CMenu::GetItems()
{
	return m_items;
}

void CMenu::print()
{
	for (int i = 0; i < m_count; i++)
	{
		std::cout << i << ". ";
		m_items[i].PrintItemName();
		std::cout << '\n';
	}
}

int CMenu::runCommand()
{
	print();
	std::cout << "Enter command: ";
	int command;
	std::cin >> command;
	return m_items[command].run();
}