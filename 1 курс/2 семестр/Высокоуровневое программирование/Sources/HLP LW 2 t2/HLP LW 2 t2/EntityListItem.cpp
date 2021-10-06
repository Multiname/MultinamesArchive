//#include "EntityListItem.h"
//#include "Dialogue.h"
//#include "Interest.h"
//#include "Reminder.h"
//#include "Theme.h"
//#include "User.h"
//#include "Constants.h"
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <Windows.h>
//#include "Add.h"
//
//using namespace KMK;
//
//EntityListItem::EntityListItem(EntityMode entityMode, char* itemName, char* entityDatabase, char* idCounterDatabase):
//	MenuItem(itemName)
//{
//	m_entityMode = entityMode;
//
//	m_entityDatabase = new char[LENGTH_OF_FIELD] {};
//	strcpy_s(m_entityDatabase, LENGTH_OF_FIELD, entityDatabase);
//	m_idCounterDatabase = new char[LENGTH_OF_FIELD] {};
//	strcpy_s(m_idCounterDatabase, LENGTH_OF_FIELD, idCounterDatabase);
//
//	m_idCounter = { idCounterDatabase };
//
//	ReadFile();
//}
//
//int EntityListItem::Run()
//{
//	unsigned short command = 0;
//
//	while (command != EXIT)
//	{
//		Draw();
//		std::cin >> command;
//		std::cin.ignore();
//		std::cout << '\n';
//
//		if (command == RESET)
//		{
//			ReadFile();
//		}
//		else if (command == ADD)
//		{
//			Entity* newEntity{};
//
//			if (IsTextEntity())
//			{
//				char* content = new char[LENGTH_OF_FIELD];
//				switch (m_entityMode)
//				{
//				case DIALOGUE:
//					std::cout << "Input message: ";
//					break;
//				case INTEREST:
//					std::cout << "Input interest: ";
//					break;
//				case REMINDER:
//					std::cout << "Input reminder: ";
//					break;
//				case THEME:
//					std::cout << "Input theme: ";
//					break;
//				}
//				std::cin.getline(content, LENGTH_OF_FIELD, '\n');
//
//				Id ownerId;
//				if (m_entityMode != DIALOGUE)
//				{
//					std::cout << "Input owner ID: ";
//				}
//				else
//				{
//					std::cout << "Input sender ID: ";
//				}
//				std::cin >> ownerId;
//				std::cin.ignore();
//
//				SYSTEMTIME systemTime;
//				GetLocalTime(&systemTime);
//
//				if (m_entityMode == DIALOGUE)
//				{
//					Id adresseeId;
//					std::cout << "Input adressee ID: ";
//					std::cin >> adresseeId;
//					std::cin.ignore();
//
//					newEntity = new Dialogue(m_idCounter(), { systemTime.wDay, systemTime.wMonth, systemTime.wYear }, content, ownerId, adresseeId);
//				}
//				else if (m_entityMode == INTEREST)
//				{
//					newEntity = new Interest(m_idCounter(), { systemTime.wDay, systemTime.wMonth, systemTime.wYear }, content, ownerId);
//				}
//				else if (m_entityMode == REMINDER)
//				{
//					unsigned short day;
//					std::cout << "Input reminder day: ";
//					std::cin >> day;
//
//					unsigned short month;
//					std::cout << "Input reminder month: ";
//					std::cin >> month;
//
//					unsigned short year;
//					std::cout << "Input reminder year: ";
//					std::cin >> year;
//					std::cin.ignore();
//
//					newEntity = new Reminder(m_idCounter(), { systemTime.wDay, systemTime.wMonth, systemTime.wYear }, content, ownerId, { day, month, year });
//				}
//			}
//
//			Add(m_entityList, m_size, newEntity);
//		}
//		else if (command == REMOVE)
//		{
//			std::cout << "Input ID: ";
//			Id id;
//			std::cin >> id;
//			std::cin.ignore();
//
//			m_themeList = Remove(m_themeList, m_size, id, m_size);
//		}
//		else if (command == EDIT)
//		{
//			std::cout << "Input ID: ";
//			Id id;
//			std::cin >> id;
//			std::cin.ignore();
//			std::cout << '\n';
//
//			std::cout << "Fields to edit\n";
//			std::cout << "0. ID\n";
//			std::cout << "1. Date\n";
//			std::cout << "2. Theme\n";
//			std::cout << "3. Owner ID\n";
//			std::cout << "Choose field: ";
//			unsigned short fieldToChange;
//			std::cin >> fieldToChange;
//			std::cin.ignore();
//			std::cout << '\n';
//
//			if (fieldToChange == 0)
//			{
//				std::cout << "Input new ID: ";
//				Id* newId = new Id{};
//				std::cin >> *newId;
//				std::cin.ignore();
//				m_themeList = Edit(m_themeList, m_size, id, (void*)newId, EditMode::ID);
//			}
//			if (fieldToChange == 1)
//			{
//				std::cout << "Input new date\n";
//				std::cout << "Day: ";
//				unsigned short day;
//				std::cin >> day;
//				std::cout << "Month: ";
//				unsigned short month;
//				std::cin >> month;
//				std::cout << "Year: ";
//				unsigned short year;
//				std::cin >> year;
//				std::cin.ignore();
//				m_themeList = Edit(m_themeList, m_size, id, (void*)new Entity::Date{ day, month, year }, EditMode::DATE);
//			}
//			if (fieldToChange == 2)
//			{
//				std::cout << "Input new theme: ";
//				char* theme = new char[LENGTH_OF_FIELD] {};
//				std::cin.getline(theme, LENGTH_OF_FIELD, '\n');
//				m_themeList = Edit(m_themeList, m_size, id, (void*)theme, EditMode::CONTENT);
//			}
//			if (fieldToChange == 3)
//			{
//				std::cout << "Input new owner ID: ";
//				Id* newOwnerId = new Id{};
//				std::cin >> *newOwnerId;
//				std::cin.ignore();
//				m_themeList = Edit(m_themeList, m_size, id, (void*)newOwnerId, EditMode::OWNER_ID);
//			}
//		}
//		else if (command == SORT)
//		{
//			std::cout << "Orders for sort\n";
//			std::cout << "0. Descending\n";
//			std::cout << "1. Ascending\n";
//			std::cout << "Choose order: ";
//			unsigned short order;
//			std::cin >> order;
//			std::cout << '\n';
//
//			std::cout << "Fields for sort\n";
//			std::cout << "0. ID\n";
//			std::cout << "1. Date\n";
//			std::cout << "2. Theme\n";
//			std::cout << "3. Owner ID\n";
//			std::cout << "Choose field: ";
//			unsigned short field;
//			std::cin >> field;
//			std::cin.ignore();
//			SortMode sortMode = (SortMode)-1;
//			switch (field)
//			{
//			case 0:
//				sortMode = SortMode::ID;
//				break;
//			case 1:
//				sortMode = SortMode::DATE;
//				break;
//			case 2:
//				sortMode = SortMode::CONTENT;
//				break;
//			case 3:
//				sortMode = SortMode::OWNER_ID;
//				break;
//			}
//			m_themeList = Sort(m_themeList, m_size, (OrderMode)order, sortMode);
//		}
//		else if (command == FILTER)
//		{
//			std::cout << "Fields for filter\n";
//			std::cout << "0. ID\n";
//			std::cout << "1. Date\n";
//			std::cout << "2. Theme\n";
//			std::cout << "3. Owner ID\n";
//			std::cout << "Choose field: ";
//			unsigned short field;
//			std::cin >> field;
//			std::cin.ignore();
//			std::cout << '\n';
//
//			if (field == 0)
//			{
//				std::cout << "Input part of ID: ";
//				Id id;
//				std::cin >> id;
//				std::cin.ignore();
//				m_themeList = Filter(m_themeList, m_size, (void*)&id, FilterMode::ID, m_size);
//			}
//			if (field == 1)
//			{
//				std::cout << "Input date (if you don't want to filter by the field, input 0)\n";
//				std::cout << "Day: ";
//				unsigned short day;
//				std::cin >> day;
//				std::cout << "Month: ";
//				unsigned short month;
//				std::cin >> month;
//				std::cout << "Year: ";
//				unsigned short year;
//				std::cin >> year;
//				std::cin.ignore();
//				m_themeList = Filter(m_themeList, m_size, (void*)new Entity::Date{ day, month, year }, FilterMode::DATE, m_size);
//			}
//			if (field == 2)
//			{
//				std::cout << "Input part of theme: ";
//				char* theme = new char[LENGTH_OF_FIELD] {};
//				std::cin.getline(theme, LENGTH_OF_FIELD, '\n');
//				m_themeList = Filter(m_themeList, m_size, (void*)theme, FilterMode::CONTENT, m_size);
//			}
//			if (field == 3)
//			{
//				std::cout << "Input part of owner ID: ";
//				Id ownerId;
//				std::cin >> ownerId;
//				std::cin.ignore();
//				m_themeList = Filter(m_themeList, m_size, (void*)&ownerId, FilterMode::OWNER_ID, m_size);
//			}
//		}
//
//		if (command == ADD || command == REMOVE || command == EDIT)
//		{
//			std::ofstream fileWrite(m_themeDatabase, std::ios::binary);
//			fileWrite.write((char*)&m_size, sizeof(size_t));
//			for (Iteration i{}; i < m_size; ++i)
//			{
//				fileWrite.write((char*)new Id{ m_themeList[i]->GetId() }, sizeof(Id));
//				fileWrite.write((char*)&m_themeList[i]->GetDate(), sizeof(Entity::Date));
//				fileWrite.write(m_themeList[i]->GetContent(), LENGTH_OF_FIELD);
//				fileWrite.write((char*)new Id{ m_themeList[i]->GetOwnerId() }, sizeof(Id));
//			}
//			fileWrite.close();
//		}
//
//		system("cls");
//	}
//
//	return 0;
//}
//
//bool EntityListItem::IsTextEntity()
//{
//	return (m_entityMode == DIALOGUE || m_entityMode == INTEREST || m_entityMode == REMINDER || m_entityMode == THEME);
//}
//
//void EntityListItem::Draw()
//{
//	if (IsTextEntity())
//	{
//		unsigned short maximumContentLength{};
//
//		if (m_entityMode == DIALOGUE)
//		{
//			maximumContentLength = 7;
//		}
//		else if (m_entityMode == INTEREST || m_entityMode == REMINDER)
//		{
//			maximumContentLength = 8;
//		}
//		else if (m_entityMode == THEME)
//		{
//			maximumContentLength = 5;
//		}
//
//		for (Iteration i{}; i < m_size; ++i)
//		{
//			if (strlen(dynamic_cast<TextEntity*>(m_entityList[i])->GetContent()) > maximumContentLength)
//			{
//				maximumContentLength = strlen(dynamic_cast<TextEntity*>(m_entityList[i])->GetContent());
//			}
//		}
//
//		if (m_entityMode == DIALOGUE)
//		{
//			std::cout << std::setw((11 + 3 + 3 + 5 + maximumContentLength + 1 + 11 + 11 + 6 + strlen(GetItemName())) / 2) << GetItemName() << "\n\n";
//			std::cout << std::setw(11) << "ID" << "|";
//			std::cout << std::setw(3) << "dd" << "|";
//			std::cout << std::setw(3) << "mm" << "|";
//			std::cout << std::setw(5) << "yyyy" << "|";
//			std::cout << std::setw(maximumContentLength + 1) << "Message" << "|";
//			std::cout << std::setw(11) << "Sender ID" << "|";
//			std::cout << std::setw(11) << "Adressee ID";
//			std::cout << '\n';
//		}
//		else if (m_entityMode == INTEREST)
//		{
//			std::cout << std::setw((11 + 3 + 3 + 5 + maximumContentLength + 1 + 11 + 5 + strlen(GetItemName())) / 2) << GetItemName() << "\n\n";
//			std::cout << std::setw(11) << "ID" << "|";
//			std::cout << std::setw(3) << "dd" << "|";
//			std::cout << std::setw(3) << "mm" << "|";
//			std::cout << std::setw(5) << "yyyy" << "|";
//			std::cout << std::setw(maximumContentLength + 1) << "Interest" << "|";
//			std::cout << std::setw(11) << "Owner ID";
//			std::cout << '\n';
//		}
//		else if (m_entityMode == REMINDER)
//		{
//			std::cout << std::setw((11 + 3 + 3 + 5 + 11 + maximumContentLength + 1 + 3 + 3 + 5 + 8 + strlen(GetItemName())) / 2) << GetItemName() << "\n\n";
//			std::cout << std::setw(11) << "ID" << "|";
//			std::cout << std::setw(3) << "dd" << "|";
//			std::cout << std::setw(3) << "mm" << "|";
//			std::cout << std::setw(5) << "yyyy" << "|";
//			std::cout << std::setw(11) << "Owner ID" << "|";
//			std::cout << std::setw(maximumContentLength + 1) << "Reminder" << ":";
//			std::cout << std::setw(3) << "dd" << "|";
//			std::cout << std::setw(3) << "mm" << "|";
//			std::cout << std::setw(5) << "yyyy";
//			std::cout << '\n';
//		}
//		else if (m_entityMode == THEME)
//		{
//			std::cout << std::setw((11 + 3 + 3 + 5 + maximumContentLength + 1 + 11 + 5 + strlen(GetItemName())) / 2) << GetItemName() << "\n\n";
//			std::cout << std::setw(11) << "ID" << "|";
//			std::cout << std::setw(3) << "dd" << "|";
//			std::cout << std::setw(3) << "mm" << "|";
//			std::cout << std::setw(5) << "yyyy" << "|";
//			std::cout << std::setw(maximumContentLength + 1) << "Theme" << "|";
//			std::cout << std::setw(11) << "Owner ID";
//			std::cout << '\n';
//		}
//
//		for (Iteration i{}; i < m_size; ++i)
//		{
//			std::cout << std::setw(11) << m_entityList[i]->GetId() << "|";
//			std::cout << std::setw(3) << m_entityList[i]->GetDate().day << "|";
//			std::cout << std::setw(3) << m_entityList[i]->GetDate().month << "|";
//			std::cout << std::setw(5) << m_entityList[i]->GetDate().year << "|";
//			if (m_entityMode != REMINDER)
//			{
//				std::cout << std::setw(maximumContentLength + 1) << dynamic_cast<TextEntity*>(m_entityList[i])->GetContent() << "|";
//			}
//			std::cout << std::setw(11) << dynamic_cast<TextEntity*>(m_entityList[i])->GetOwnerId();
//			if (m_entityMode == DIALOGUE)
//			{
//				std::cout << std::setw(11) << dynamic_cast<Dialogue*>(m_entityList[i])->GetAdresseeId();
//			}
//			else if (m_entityMode == REMINDER)
//			{
//				std::cout << std::setw(maximumContentLength + 1) << dynamic_cast<TextEntity*>(m_entityList[i])->GetContent() << "|";
//				std::cout << std::setw(3) << dynamic_cast<Reminder*>(m_entityList[i])->GetReminderTime().day << "|";
//				std::cout << std::setw(3) << dynamic_cast<Reminder*>(m_entityList[i])->GetReminderTime().month << "|";
//				std::cout << std::setw(5) << dynamic_cast<Reminder*>(m_entityList[i])->GetReminderTime().year;
//			}
//			std::cout << '\n';
//		}
//	}
//	else if (m_entityMode == USER)
//	{
//		unsigned short maximumNameLength = 4;
//		unsigned short maximumLoginLength = 5;
//		unsigned short maximumPasswordLength = 8;
//		for (Iteration i{}; i < m_size; ++i)
//		{
//			if (strlen(dynamic_cast<User*>(m_entityList[i])->GetName()) > maximumNameLength)
//			{
//				maximumNameLength = strlen(dynamic_cast<User*>(m_entityList[i])->GetName());
//			}
//			if (strlen(dynamic_cast<User*>(m_entityList[i])->GetLogin()) > maximumLoginLength)
//			{
//				maximumLoginLength = strlen(dynamic_cast<User*>(m_entityList[i])->GetLogin());
//			}
//			if (strlen(dynamic_cast<User*>(m_entityList[i])->GetPassword()) > maximumPasswordLength)
//			{
//				maximumPasswordLength = strlen(dynamic_cast<User*>(m_entityList[i])->GetPassword());
//			}
//		}
//
//		std::cout << std::setw((11 + 3 + 3 + 5 + maximumNameLength + 1 + maximumLoginLength + 1 + maximumPasswordLength + 1 + 6 + strlen(GetItemName())) / 2) << GetItemName() << "\n\n";
//		std::cout << std::setw(11) << "ID" << "|";
//		std::cout << std::setw(3) << "dd" << "|";
//		std::cout << std::setw(3) << "mm" << "|";
//		std::cout << std::setw(5) << "yyyy" << "|";
//		std::cout << std::setw(maximumNameLength + 1) << "Name" << "|";
//		std::cout << std::setw(maximumLoginLength + 1) << "Login" << "|";
//		std::cout << std::setw(maximumPasswordLength + 1) << "Password";
//		std::cout << '\n';
//
//		for (Iteration i{}; i < m_size; ++i)
//		{
//			std::cout << std::setw(11) << m_entityList[i]->GetId() << "|";
//			std::cout << std::setw(3) << m_entityList[i]->GetDate().day << "|";
//			std::cout << std::setw(3) << m_entityList[i]->GetDate().month << "|";
//			std::cout << std::setw(5) << m_entityList[i]->GetDate().year << "|";
//			std::cout << std::setw(maximumNameLength + 1) << dynamic_cast<User*>(m_entityList[i])->GetName() << "|";
//			std::cout << std::setw(maximumLoginLength + 1) << dynamic_cast<User*>(m_entityList[i])->GetLogin() << "|";
//			std::cout << std::setw(maximumPasswordLength + 1) << dynamic_cast<User*>(m_entityList[i])->GetPassword();
//			std::cout << '\n';
//		}
//	}
//
//	std::cout << '\n';
//	std::cout << RESET << ". Reset list\n";
//	std::cout << ADD << ". Add new\n";
//	std::cout << REMOVE << ". Delete\n";
//	std::cout << EDIT << ". Edit\n";
//	std::cout << SORT << ". Sort list\n";
//	std::cout << FILTER << ". Filter list\n";
//	std::cout << ID << ". Choose ID\n";
//	std::cout << EXIT << ". Exit\n";
//	std::cout << "Input command: ";
//}
//
//void EntityListItem::ReadFile()
//{
//	std::ifstream fileRead(m_entityDatabase, std::ios::binary);
//	fileRead.read((char*)&m_size, sizeof(size_t));
//	m_entityList = new Entity * [m_size] {};
//	for (Iteration i{}; i < m_size; ++i)
//	{
//		Id id{};
//		fileRead.read((char*)&id, sizeof(Id));
//
//		Entity::Date date{};
//		fileRead.read((char*)&date, sizeof(Entity::Date));
//
//		if (IsTextEntity())
//		{
//			char* content = new char[LENGTH_OF_FIELD] {};
//			fileRead.read(content, LENGTH_OF_FIELD);
//
//			Id ownerId{};
//			fileRead.read((char*)&ownerId, sizeof(Id));
//
//			if (m_entityMode == DIALOGUE)
//			{
//				Id adresseeId{};
//				fileRead.read((char*)&adresseeId, sizeof(Id));
//
//				m_entityList[i] = new Dialogue{ id, date, content, ownerId, adresseeId };
//			}
//			else if (m_entityMode == INTEREST)
//			{
//				m_entityList[i] = new Interest{ id, date, content, ownerId };
//			}
//			else if (m_entityMode == REMINDER)
//			{
//				Entity::Date reminderTime{};
//				fileRead.read((char*)&reminderTime, sizeof(Entity::Date));
//
//				m_entityList[i] = new Reminder{ id, date, content, ownerId, reminderTime };
//			}
//			else if (m_entityMode == THEME)
//			{
//				m_entityList[i] = new Theme{ id, date, content, ownerId };
//			}
//		}
//		else if (m_entityMode == USER)
//		{
//			char* name = new char[LENGTH_OF_FIELD] {};
//			fileRead.read(name, LENGTH_OF_FIELD);
//
//			char* login = new char[LENGTH_OF_FIELD] {};
//			fileRead.read(login, LENGTH_OF_FIELD);
//
//			char* password = new char[LENGTH_OF_FIELD] {};
//			fileRead.read(password, LENGTH_OF_FIELD);
//
//			m_entityList[i] = new User{ id, date, name, login, password };
//		}
//	}
//	fileRead.close();
//}