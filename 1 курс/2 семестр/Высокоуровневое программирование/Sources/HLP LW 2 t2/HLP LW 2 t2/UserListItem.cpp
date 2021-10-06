#include "UserListItem.h"
#include <iostream>
#include <fstream>
#include "Add.h"
#include <Windows.h>
#include "Remove.h"
#include "Edit.h"
#include "Sort.h"
#include "Filter.h"
#include <iomanip>

using namespace KMK;

UserListItem::UserListItem(std::string itemName, Storage* storage) :
	MenuItem(itemName)
{
	m_storage = storage;
}

int UserListItem::Run()
{
	enum  Command 
	{
		RESET,
		ADD,
		REMOVE,
		EDIT,
		SORT,
		FILTER,
		ID,
		EXIT
	};

	unsigned short command = 0;

	while (command != EXIT)
	{
		unsigned short maximumNameLength = 4;
		unsigned short maximumLoginLength = 5;
		unsigned short maximumPasswordLength = 8;
		for (Iteration i{}; i < m_storage->GetUserListSize(); ++i)
		{
			if (m_storage->m_userList[i]->GetName().length() > maximumNameLength)
			{
				maximumNameLength = m_storage->m_userList[i]->GetName().length();
			}
			if (m_storage->m_userList[i]->GetLogin().length() > maximumLoginLength)
			{
				maximumLoginLength = m_storage->m_userList[i]->GetLogin().length();
			}
			if (m_storage->m_userList[i]->GetPassword().length() > maximumPasswordLength)
			{
				maximumPasswordLength = m_storage->m_userList[i]->GetPassword().length();
			}
		}
		
		std::cout << std::setw((11 + 3 + 3 + 5 + maximumNameLength + 1 + maximumLoginLength + 1 + maximumPasswordLength + 1 + 6 + GetItemName().length()) / 2) << GetItemName() << "\n\n";
		std::cout << std::setw(11) << "ID" << "|";
		std::cout << std::setw(3) << "dd" << "|";
		std::cout << std::setw(3) << "mm" << "|";
		std::cout << std::setw(5) << "yyyy" << "|";
		std::cout << std::setw(maximumNameLength + 1) << "Name" << "|";
		std::cout << std::setw(maximumLoginLength + 1) << "Login" << "|";
		std::cout << std::setw(maximumPasswordLength + 1) << "Password";
		std::cout << '\n';

		for (Iteration i{}; i < m_storage->GetUserListSize(); ++i)
		{
			std::cout << std::setw(11) << m_storage->m_userList[i]->GetId() << "|";
			std::cout << std::setw(3) << m_storage->m_userList[i]->GetDate().day << "|";
			std::cout << std::setw(3) << m_storage->m_userList[i]->GetDate().month << "|";
			std::cout << std::setw(5) << m_storage->m_userList[i]->GetDate().year << "|";
			std::cout << std::setw(maximumNameLength + 1) << m_storage->m_userList[i]->GetName() << "|";
			std::cout << std::setw(maximumLoginLength + 1) << m_storage->m_userList[i]->GetLogin() << "|";
			std::cout << std::setw(maximumPasswordLength + 1) << m_storage->m_userList[i]->GetPassword();
			std::cout << '\n';
		}

		std::cout << '\n';
		std::cout << RESET << ". Reset list\n";
		std::cout << ADD << ". Add new user\n";
		std::cout << REMOVE << ". Delete user\n";
		std::cout << EDIT << ". Edit user\n";
		std::cout << SORT << ". Sort list\n";
		std::cout << FILTER << ". Filter list\n";
		std::cout << ID << ". Choose ID\n";
		std::cout << EXIT << ". Exit\n";
		std::cout << "Input command: ";
		std::cin >> command;
		std::cin.ignore();
		std::cout << '\n';

		size_t size = m_storage->GetUserListSize();

		if (command == RESET)
		{
			m_storage->LoadUserList();
		}
		else if (command == ADD)
		{
			std::string name{};
			std::cout << "Input name: ";
			std::getline(std::cin, name);

			std::string login{};
			std::cout << "Input login: ";
			std::getline(std::cin, login);

			std::string password{};
			std::cout << "Input password: ";
			std::getline(std::cin, password);

			SYSTEMTIME systemTime;
			GetLocalTime(&systemTime);
			User* newUser = new User(m_storage->GetNextUserId(), { systemTime.wDay, systemTime.wMonth, systemTime.wYear }, name, login, password);

			m_storage->LoadUserList();
			size = m_storage->GetUserListSize();
			Add<User>(m_storage->m_userList, size, newUser);
			m_storage->SetUserListSize(size);
		}
		else if (command == REMOVE)
		{
			std::cout << "Input ID: ";
			Id id;
			std::cin >> id;
			std::cin.ignore();

			m_storage->LoadUserList();
			size = m_storage->GetUserListSize();
			Remove((Entity**&)m_storage->m_userList, size, id);
			m_storage->SetUserListSize(size);
		}
		else if (command == EDIT)
		{
			std::cout << "Input ID: ";
			Id id;
			std::cin >> id;
			std::cin.ignore();
			std::cout << '\n';

			std::cout << "Fields to edit\n";
			std::cout << "0. ID\n";
			std::cout << "1. Date\n";
			std::cout << "2. Name\n";
			std::cout << "3. Login\n";
			std::cout << "4. Password\n";
			std::cout << "Choose field: ";
			unsigned short fieldToChange;
			std::cin >> fieldToChange;
			std::cin.ignore();
			std::cout << '\n';

			if (fieldToChange == 0)
			{
				std::cout << "Input new ID: ";
				Id* newId = new Id{};
				std::cin >> *newId;
				std::cin.ignore();
				m_storage->LoadUserList();
				size = m_storage->GetUserListSize();
				Edit((Entity**&)m_storage->m_userList, size, id, (void*)newId, FieldMode::ID);
				delete newId;
			}
			if (fieldToChange == 1)
			{
				std::cout << "Input new date\n";
				std::cout << "Day: ";
				unsigned short day;
				std::cin >> day;
				std::cout << "Month: ";
				unsigned short month;
				std::cin >> month;
				std::cout << "Year: ";
				unsigned short year;
				std::cin >> year;
				std::cin.ignore();
				Entity::Date* newDate = new Entity::Date{ day, month, year };
				m_storage->LoadUserList();
				size = m_storage->GetUserListSize();
				Edit((Entity**&)m_storage->m_userList, size, id, (void*)newDate, FieldMode::DATE);
				delete newDate;
			}
			if (fieldToChange == 2)
			{
				std::cout << "Input new name: ";
				std::string* name = new std::string{};
				std::getline(std::cin, *name);
				m_storage->LoadUserList();
				size = m_storage->GetUserListSize();
				Edit((Entity**&)m_storage->m_userList, size, id, (void*)name, FieldMode::NAME);
				delete name;
			}
			if (fieldToChange == 3)
			{
				std::cout << "Input new login: ";
				std::string* login = new std::string{};
				std::getline(std::cin, *login);
				m_storage->LoadUserList();
				size = m_storage->GetUserListSize();
				Edit((Entity**&)m_storage->m_userList, size, id, (void*)login, FieldMode::LOGIN);
				delete login;
			}
			if (fieldToChange == 4)
			{
				std::cout << "Input new password: ";
				std::string* password = new std::string{};
				std::getline(std::cin, *password);
				m_storage->LoadUserList();
				size = m_storage->GetUserListSize();
				Edit((Entity**&)m_storage->m_userList, size, id, (void*)password, FieldMode::PASSWORD);
				delete password;
			}
		}
		else if (command == SORT)
		{
			std::cout << "Orders for sort\n";
			std::cout << "0. Descending\n";
			std::cout << "1. Ascending\n";
			std::cout << "Choose order: ";
			unsigned short order;
			std::cin >> order;
			std::cout << '\n';

			std::cout << "Fields for sort\n";
			std::cout << "0. ID\n";
			std::cout << "1. Date\n";
			std::cout << "2. Name\n";
			std::cout << "3. Login\n";
			std::cout << "4. Password\n";
			std::cout << "Choose field: ";
			unsigned short field;
			std::cin >> field;
			std::cin.ignore();
			FieldMode sortMode = (FieldMode)-1;
			switch (field)
			{
			case 0:
				sortMode = FieldMode::ID;
				break;
			case 1:
				sortMode = FieldMode::DATE;
				break;
			case 2:
				sortMode = FieldMode::NAME;
				break;
			case 3:
				sortMode = FieldMode::LOGIN;
				break;
			case 4:
				sortMode = FieldMode::PASSWORD;
				break;
			}
			Sort((Entity**&)m_storage->m_userList, size, (OrderMode)order, sortMode);
		}
		else if (command == FILTER)
		{
			std::cout << "Fields for filter\n";
			std::cout << "0. ID\n";
			std::cout << "1. Date\n";
			std::cout << "2. Name\n";
			std::cout << "3. Login\n";
			std::cout << "4. Password\n";
			std::cout << "Choose field: ";
			unsigned short field;
			std::cin >> field;
			std::cin.ignore();
			std::cout << '\n';

			if (field == 0)
			{
				std::cout << "Input part of ID: ";
				Id id;
				std::cin >> id;
				std::cin.ignore();
				Filter((Entity**&)m_storage->m_userList, size, id, FieldMode::ID);
			}
			if (field == 1)
			{
				std::cout << "Input date (if you don't want to filter by the field, input 0)\n";
				std::cout << "Day: ";
				unsigned short day;
				std::cin >> day;
				std::cout << "Month: ";
				unsigned short month;
				std::cin >> month;
				std::cout << "Year: ";
				unsigned short year;
				std::cin >> year;
				std::cin.ignore();
				Entity::Date date{ day, month, year };
				Filter((Entity**&)m_storage->m_userList, size, date, FieldMode::DATE);
			}
			if (field == 2)
			{
				std::cout << "Input part of name: ";
				std::string name{};
				std::getline(std::cin, name);
				Filter((Entity**&)m_storage->m_userList, size, name, FieldMode::NAME);
			}
			if (field == 3)
			{
				std::cout << "Input part of login: ";
				std::string login{};
				std::getline(std::cin, login);
				Filter((Entity**&)m_storage->m_userList, size, login, FieldMode::LOGIN);
			}
			if (field == 4)
			{
				std::cout << "Input part of password: ";
				std::string password{};
				std::getline(std::cin, password);
				Filter((Entity**&)m_storage->m_userList, size, password, FieldMode::PASSWORD);
			}
			m_storage->SetUserListSize(size);
		}

		if (command == ADD || command == REMOVE || command == EDIT)
		{
			m_storage->SaveUserList();
		}

		system("cls");
	}

	return 0;
}