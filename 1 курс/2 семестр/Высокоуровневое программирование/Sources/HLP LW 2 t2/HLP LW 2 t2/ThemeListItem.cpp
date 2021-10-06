#include "ThemeListItem.h"
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

ThemeListItem::ThemeListItem(std::string itemName, Storage* storage) :
	MenuItem(itemName)
{
	m_storage = storage;
}

int ThemeListItem::Run()
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
		size_t size = m_storage->GetThemeListSize();

		unsigned short maximumThemeLength = 5;
		for (Iteration i{}; i < size; ++i)
		{
			if (m_storage->m_themeList[i]->GetContent().length() > maximumThemeLength)
			{
				maximumThemeLength = m_storage->m_themeList[i]->GetContent().length();
			}
		}

		std::cout << std::setw((11 + 3 + 3 + 5 + maximumThemeLength + 1 + 11 + 5 + GetItemName().length()) / 2) << GetItemName() << "\n\n";
		std::cout << std::setw(11) << "ID" << "|";
		std::cout << std::setw(3) << "dd" << "|";
		std::cout << std::setw(3) << "mm" << "|";
		std::cout << std::setw(5) << "yyyy" << "|";
		std::cout << std::setw(maximumThemeLength + 1) << "Theme" << "|";
		std::cout << std::setw(11) << "Owner ID";
		std::cout << '\n';

		for (Iteration i{}; i < size; ++i)
		{
			std::cout << std::setw(11) << m_storage->m_themeList[i]->GetId() << "|";
			std::cout << std::setw(3) << m_storage->m_themeList[i]->GetDate().day << "|";
			std::cout << std::setw(3) << m_storage->m_themeList[i]->GetDate().month << "|";
			std::cout << std::setw(5) << m_storage->m_themeList[i]->GetDate().year << "|";
			std::cout << std::setw(maximumThemeLength + 1) << m_storage->m_themeList[i]->GetContent() << "|";
			std::cout << std::setw(11) << m_storage->m_themeList[i]->GetOwnerId();
			std::cout << '\n';
		}

		std::cout << '\n';
		std::cout << RESET << ". Reset list\n";
		std::cout << ADD << ". Add new theme\n";
		std::cout << REMOVE << ". Delete theme\n";
		std::cout << EDIT << ". Edit theme\n";
		std::cout << SORT << ". Sort list\n";
		std::cout << FILTER << ". Filter list\n";
		std::cout << ID << ". Choose ID\n";
		std::cout << EXIT << ". Exit\n";
		std::cout << "Input command: ";
		std::cin >> command;
		std::cin.ignore();
		std::cout << '\n';

		if (command == RESET)
		{
			m_storage->LoadThemeList();
		}
		else if (command == ADD)
		{
			std::string theme{};
			std::cout << "Input theme: ";
			std::getline(std::cin, theme);

			Id ownerId;
			std::cout << "Input owner ID: ";
			std::cin >> ownerId;
			std::cin.ignore();

			SYSTEMTIME systemTime;
			GetLocalTime(&systemTime);
			Theme* newTheme = new Theme(m_storage->GetNextThemeId(), { systemTime.wDay, systemTime.wMonth, systemTime.wYear }, theme, ownerId);

			m_storage->LoadThemeList();
			size = m_storage->GetThemeListSize();
			Add<Theme>(m_storage->m_themeList, size, newTheme);
			m_storage->SetThemeListSize(size);
		}
		else if (command == REMOVE)
		{
			std::cout << "Input ID: ";
			Id id;
			std::cin >> id;
			std::cin.ignore();

			m_storage->LoadThemeList();
			size = m_storage->GetThemeListSize();
			Remove((Entity**&)m_storage->m_themeList, size, id);
			m_storage->SetThemeListSize(size);
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
			std::cout << "2. Theme\n";
			std::cout << "3. Owner ID\n";
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
				m_storage->LoadThemeList();
				size = m_storage->GetThemeListSize();
				Edit((Entity**&)m_storage->m_themeList, size, id, (void*)newId, FieldMode::ID);
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
				m_storage->LoadThemeList();
				size = m_storage->GetThemeListSize();
				Edit((Entity**&)m_storage->m_themeList, size, id, (void*)newDate, FieldMode::DATE);
				delete newDate;
			}
			if (fieldToChange == 2)
			{
				std::cout << "Input new theme: ";
				std::string* theme = new std::string{};
				std::getline(std::cin, *theme);
				m_storage->LoadThemeList();
				size = m_storage->GetThemeListSize();
				Edit((Entity**&)m_storage->m_themeList, size, id, (void*)theme, FieldMode::CONTENT);
				delete theme;
			}
			if (fieldToChange == 3)
			{
				std::cout << "Input new owner ID: ";
				Id* newOwnerId = new Id{};
				std::cin >> *newOwnerId;
				std::cin.ignore();
				m_storage->LoadThemeList();
				size = m_storage->GetThemeListSize();
				Edit((Entity**&)m_storage->m_themeList, size, id, (void*)newOwnerId, FieldMode::OWNER_ID);
				delete newOwnerId;
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
			std::cout << "2. Theme\n";
			std::cout << "3. Owner ID\n";
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
				sortMode = FieldMode::CONTENT;
				break;
			case 3:
				sortMode = FieldMode::OWNER_ID;
				break;
			}
			Sort((Entity**&)m_storage->m_themeList, size, (OrderMode)order, sortMode);
		}
		else if (command == FILTER)
		{
			std::cout << "Fields for filter\n";
			std::cout << "0. ID\n";
			std::cout << "1. Date\n";
			std::cout << "2. Theme\n";
			std::cout << "3. Owner ID\n";
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
				Filter((Entity**&)m_storage->m_themeList, size, id, FieldMode::ID);
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
				Entity::Date date { day, month, year };
				Filter((Entity**&)m_storage->m_themeList, size, date, FieldMode::DATE);
			}
			if (field == 2)
			{
				std::cout << "Input part of theme: ";
				std::string theme{};
				std::getline(std::cin, theme);
				Filter((Entity**&)m_storage->m_themeList, size, theme, FieldMode::CONTENT);
			}
			if (field == 3)
			{
				std::cout << "Input part of owner ID: ";
				Id ownerId;
				std::cin >> ownerId;
				std::cin.ignore();
				Filter((Entity**&)m_storage->m_themeList, size, ownerId, FieldMode::OWNER_ID);
			}
			m_storage->SetThemeListSize(size);
		}

		if (command == ADD || command == REMOVE || command == EDIT)
		{
			m_storage->SaveThemeList();
		}

		system("cls");
	}

	return 0;
}