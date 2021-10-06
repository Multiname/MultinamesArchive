#include "Users.h"
#include <iostream>

using namespace KMK;

Users::Users(char* item_name, ItemMenu* users, size_t numOfUsers, ItemMenu* newUser, ItemMenu* format) :
	ItemMenu(item_name, nullptr)
{
	m_users = users;
	m_numOfUsers = numOfUsers;
	m_newUser = newUser;
	m_format = format;
}

char* Users::GetItemName()
{
	return ItemMenu::GetItemName();
}

void  Users::PrintItemName()
{
	ItemMenu::PrintItemName();
}

int  Users::run()
{
	std::cout << "0. ";
	m_newUser->PrintItemName();
	std::cout << '\n';

	std::cout << "1. ";
	m_format->PrintItemName();
	std::cout << '\n';

	for (int i = 0; i < m_numOfUsers; i++)
	{
		std::cout << i + 2 << ". ";
		m_users[i].PrintItemName();
		std::cout << '\n';
	}

	std::cout << "Enter command: ";
	int command;
	std::cin >> command;
	if (command == 0)
	{
		m_newUser->run();
	}
	else if (command == 1)
	{
		m_format->run();
	}
	else
	{
		m_users[command].run();
	}

	return 0;
}