#include "ReminderListItem.h"
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

ReminderListItem::ReminderListItem(std::string itemName, Storage* storage) :
	MenuItem(itemName)
{
	m_storage = storage;
}

int ReminderListItem::Run()
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
		size_t size = m_storage->GetReminderListSize();

		unsigned short maximumReminderLength = 8;
		for (Iteration i{}; i < size; ++i)
		{
			if (m_storage->m_reminderList[i]->GetContent().length() > maximumReminderLength)
			{
				maximumReminderLength = m_storage->m_reminderList[i]->GetContent().length();
			}
		}

		std::cout << std::setw((11 + 3 + 3 + 5 + 11 + maximumReminderLength + 1 + 3 + 3 + 5 + 8 + GetItemName().length()) / 2) << GetItemName() << "\n\n";
		std::cout << std::setw(11) << "ID" << "|";
		std::cout << std::setw(3) << "dd" << "|";
		std::cout << std::setw(3) << "mm" << "|";
		std::cout << std::setw(5) << "yyyy" << "|";
		std::cout << std::setw(11) << "Owner ID" << "|";
		std::cout << std::setw(maximumReminderLength + 1) << "Reminder" << ":";
		std::cout << std::setw(3) << "dd" << "|";
		std::cout << std::setw(3) << "mm" << "|";
		std::cout << std::setw(5) << "yyyy";
		std::cout << '\n';

		for (Iteration i{}; i < size; ++i)
		{
			std::cout << std::setw(11) << m_storage->m_reminderList[i]->GetId() << "|";
			std::cout << std::setw(3) << m_storage->m_reminderList[i]->GetDate().day << "|";
			std::cout << std::setw(3) << m_storage->m_reminderList[i]->GetDate().month << "|";
			std::cout << std::setw(5) << m_storage->m_reminderList[i]->GetDate().year << "|";
			std::cout << std::setw(11) << m_storage->m_reminderList[i]->GetOwnerId() << "|";
			std::cout << std::setw(maximumReminderLength + 1) << m_storage->m_reminderList[i]->GetContent() << ":";
			std::cout << std::setw(3) << m_storage->m_reminderList[i]->GetReminderTime().day << "|";
			std::cout << std::setw(3) << m_storage->m_reminderList[i]->GetReminderTime().month << "|";
			std::cout << std::setw(5) << m_storage->m_reminderList[i]->GetReminderTime().year;
			std::cout << '\n';
		}

		std::cout << '\n';
		std::cout << RESET << ". Reset list\n";
		std::cout << ADD << ". Add new reminder\n";
		std::cout << REMOVE << ". Delete reminder\n";
		std::cout << EDIT << ". Edit reminder\n";
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
			m_storage->LoadReminderList();
		}
		else if (command == ADD)
		{
			Id ownerId;
			std::cout << "Input owner ID: ";
			std::cin >> ownerId;
			std::cin.ignore();

			std::string reminder{};
			std::cout << "Input reminder: ";
			std::getline(std::cin, reminder);

			unsigned short day;
			std::cout << "Input reminder day: ";
			std::cin >> day;

			unsigned short month;
			std::cout << "Input reminder month: ";
			std::cin >> month;

			unsigned short year;
			std::cout << "Input reminder year: ";
			std::cin >> year;
			std::cin.ignore();

			SYSTEMTIME systemTime;
			GetLocalTime(&systemTime);
			Reminder* newReminder = new Reminder(m_storage->GetNextReminderId(), { systemTime.wDay, systemTime.wMonth, systemTime.wYear }, reminder, ownerId, {day, month, year});

			m_storage->LoadReminderList();
			size = m_storage->GetReminderListSize();
			Add<Reminder>(m_storage->m_reminderList, size, newReminder);
			m_storage->SetReminderListSize(size);
		}
		else if (command == REMOVE)
		{
			std::cout << "Input ID: ";
			Id id;
			std::cin >> id;
			std::cin.ignore();

			m_storage->LoadReminderList();
			size = m_storage->GetReminderListSize();
			Remove((Entity**&)m_storage->m_reminderList, size, id);
			m_storage->SetReminderListSize(size);
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
			std::cout << "2. Owner ID\n";
			std::cout << "3. Reminder\n";
			std::cout << "4. Reminder time\n";
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
				m_storage->LoadReminderList();
				size = m_storage->GetReminderListSize();
				Edit((Entity**&)m_storage->m_reminderList, size, id, (void*)newId, FieldMode::ID);
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
				m_storage->LoadReminderList();
				size = m_storage->GetReminderListSize();
				Edit((Entity**&)m_storage->m_reminderList, size, id, (void*)newDate, FieldMode::DATE);
				delete newDate;
			}
			if (fieldToChange == 2)
			{
				std::cout << "Input new owner ID: ";
				Id* newOwnerId = new Id{};
				std::cin >> *newOwnerId;
				std::cin.ignore();
				m_storage->LoadReminderList();
				size = m_storage->GetReminderListSize();
				Edit((Entity**&)m_storage->m_reminderList, size, id, (void*)newOwnerId, FieldMode::OWNER_ID);
				delete newOwnerId;
				
			}
			if (fieldToChange == 3)
			{
				std::cout << "Input new reminder: ";
				std::string* reminder = new std::string{};
				std::getline(std::cin, *reminder);
				m_storage->LoadReminderList();
				size = m_storage->GetReminderListSize();
				Edit((Entity**&)m_storage->m_reminderList, size, id, (void*)reminder, FieldMode::CONTENT);
				delete reminder;
			}
			if (fieldToChange == 4)
			{
				std::cout << "Input new reminder time\n";
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
				Entity::Date* newReminderDate = new Entity::Date{ day, month, year };
				m_storage->LoadReminderList();
				size = m_storage->GetReminderListSize();
				Edit((Entity**&)m_storage->m_reminderList, size, id, (void*)newReminderDate, FieldMode::REMINDER_TIME);
				delete newReminderDate;
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
			std::cout << "2. Owner ID\n";
			std::cout << "3. Reminder\n";
			std::cout << "4. Reminder time\n";
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
				sortMode = FieldMode::OWNER_ID;
				break;
			case 3:
				sortMode = FieldMode::CONTENT;
				break;
			case 4:
				sortMode = FieldMode::REMINDER_TIME;
				break;
			}
			Sort((Entity**&)m_storage->m_reminderList, size, (OrderMode)order, sortMode);
		}
		else if (command == FILTER)
		{
			std::cout << "Fields for filter\n";
			std::cout << "0. ID\n";
			std::cout << "1. Date\n";
			std::cout << "2. Owner ID\n";
			std::cout << "3. Reminder\n";
			std::cout << "4. Reminder time\n";
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
				Filter((Entity**&)m_storage->m_reminderList, size, id, FieldMode::ID);
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
				Filter((Entity**&)m_storage->m_reminderList, size, date, FieldMode::DATE);
			}
			if (field == 2)
			{
				std::cout << "Input part of owner ID: ";
				Id ownerId;
				std::cin >> ownerId;
				std::cin.ignore();
				Filter((Entity**&)m_storage->m_reminderList, size, ownerId, FieldMode::OWNER_ID);
				
			}
			if (field == 3)
			{
				std::cout << "Input part of reminder: ";
				std::string reminder{};
				std::getline(std::cin, reminder);
				Filter((Entity**&)m_storage->m_reminderList, size, reminder, FieldMode::CONTENT);
			}
			if (field == 4)
			{
				std::cout << "Input reminder time (if you don't want to filter by the field, input 0)\n";
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
				Filter((Entity**&)m_storage->m_reminderList, size, date, FieldMode::REMINDER_TIME);
			}
			m_storage->SetReminderListSize(size);
		}

		if (command == ADD || command == REMOVE || command == EDIT)
		{
			m_storage->SaveReminderList();
		}

		system("cls");
	}

	return 0;
}