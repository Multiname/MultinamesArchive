#include "DialogueListItem.h"
#include <iostream>
#include <fstream>
#include "Add.h"
#include <Windows.h>
#include "Remove.h"
#include "Edit.h"
#include "Sort.h"
#include "Filter.h"
#include <iomanip>
#include <string>

using namespace KMK;

DialogueListItem::DialogueListItem(std::string itemName, Storage* storage) :
	MenuItem(itemName)
{
	m_storage = storage;
}

int DialogueListItem::Run()
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
		size_t size = m_storage->GetDialogueListSize();

		unsigned short maximumMessageLength = 7;
		for (Iteration i{}; i < size; ++i)
		{
			if (m_storage->m_dialogueList[i]->GetContent().length() > maximumMessageLength)
			{
				maximumMessageLength = m_storage->m_dialogueList[i]->GetContent().length();
			}
		}

		std::cout << std::setw((11 + 3 + 3 + 5 + maximumMessageLength + 1 + 11 + 11 + 6 + GetItemName().length()) / 2) << GetItemName() << "\n\n";
		std::cout << std::setw(11) << "ID" << "|";
		std::cout << std::setw(3) << "dd" << "|";
		std::cout << std::setw(3) << "mm" << "|";
		std::cout << std::setw(5) << "yyyy" << "|";
		std::cout << std::setw(maximumMessageLength + 1) << "Message" << "|";
		std::cout << std::setw(11) << "Sender ID" << "|";
		std::cout << std::setw(11) << "Adressee ID";
		std::cout << '\n';

		for (Iteration i{}; i < size; ++i)
		{
			std::cout << std::setw(11) << m_storage->m_dialogueList[i]->GetId() << "|";
			std::cout << std::setw(3) << m_storage->m_dialogueList[i]->GetDate().day << "|";
			std::cout << std::setw(3) << m_storage->m_dialogueList[i]->GetDate().month << "|";
			std::cout << std::setw(5) << m_storage->m_dialogueList[i]->GetDate().year << "|";
			std::cout << std::setw(maximumMessageLength + 1) << m_storage->m_dialogueList[i]->GetContent() << "|";
			std::cout << std::setw(11) << m_storage->m_dialogueList[i]->GetOwnerId() << "|";
			std::cout << std::setw(11) << m_storage->m_dialogueList[i]->GetAdresseeId();
			std::cout << '\n';
		}

		std::cout << '\n';
		std::cout << RESET << ". Reset list\n";
		std::cout << ADD << ". Add new dialogue\n";
		std::cout << REMOVE << ". Delete dialogue\n";
		std::cout << EDIT << ". Edit dialogue\n";
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
			m_storage->LoadDialogueList();
		}
		else if (command == ADD)
		{
			std::string message{};
			std::cout << "Input message: ";
			std::getline(std::cin, message);

			Id senderId;
			std::cout << "Input sender ID: ";
			std::cin >> senderId;

			Id adresseeId;
			std::cout << "Input adressee ID: ";
			std::cin >> adresseeId;
			std::cin.ignore();

			SYSTEMTIME systemTime;
			GetLocalTime(&systemTime);
			Dialogue* newDialogue = new Dialogue(m_storage->GetNextDialogueId(), { systemTime.wDay, systemTime.wMonth, systemTime.wYear }, message, senderId, adresseeId);

			m_storage->LoadDialogueList();
			size = m_storage->GetDialogueListSize();
			Add<Dialogue>(m_storage->m_dialogueList, size, newDialogue);
			m_storage->SetDialogueListSize(size);
		}
		else if (command == REMOVE)
		{
			std::cout << "Input ID: ";
			Id id;
			std::cin >> id;
			std::cin.ignore();

			m_storage->LoadDialogueList();
			size = m_storage->GetDialogueListSize();
			Remove((Entity**&)m_storage->m_dialogueList, size, id);
			m_storage->SetDialogueListSize(size);
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
			std::cout << "2. Message\n";
			std::cout << "3. Sender ID\n";
			std::cout << "4. Adressee ID\n";
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
				m_storage->LoadDialogueList();
				size = m_storage->GetDialogueListSize();
				Edit((Entity**&)m_storage->m_dialogueList, size, id, (void*)newId, FieldMode::ID);
				delete newId;
			}
			if (fieldToChange == 1)
			{
				std::cout << "Input new date\n";
				std::cout << "Day:";
				unsigned short day;
				std::cin >> day;
				std::cout << "Month:";
				unsigned short month;
				std::cin >> month;
				std::cout << "Year:";
				unsigned short year;
				std::cin >> year;
				std::cin.ignore();
				Entity::Date* newDate = new Entity::Date{ day, month, year };
				m_storage->LoadDialogueList();
				size = m_storage->GetDialogueListSize();
				Edit((Entity**&)m_storage->m_dialogueList, size, id, (void*)newDate, FieldMode::DATE);
				delete newDate;
			}
			if (fieldToChange == 2)
			{
				std::cout << "Input new message: ";
				std::string* message = new std::string{};
				std::getline(std::cin, *message);
				m_storage->LoadDialogueList();
				size = m_storage->GetDialogueListSize();
				Edit((Entity**&)m_storage->m_dialogueList, size, id, (void*)message, FieldMode::CONTENT);
				delete message;
			}
			if (fieldToChange == 3)
			{
				std::cout << "Input new sender ID: ";
				Id* newSenderId = new Id{};
				std::cin >> *newSenderId;
				std::cin.ignore();
				m_storage->LoadDialogueList();
				size = m_storage->GetDialogueListSize();
				Edit((Entity**&)m_storage->m_dialogueList, size, id, (void*)newSenderId, FieldMode::OWNER_ID);
				delete newSenderId;
			}
			if (fieldToChange == 4)
			{
				std::cout << "Input new adressee ID: ";
				Id* newAdresseeId = new Id{};
				std::cin >> *newAdresseeId;
				std::cin.ignore();
				m_storage->LoadDialogueList();
				size = m_storage->GetDialogueListSize();
				Edit((Entity**&)m_storage->m_dialogueList, size, id, (void*)newAdresseeId, FieldMode::OWNER_ID);
				delete newAdresseeId;
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
			std::cout << "2. Message\n";
			std::cout << "3. Sender ID\n";
			std::cout << "4. Adressee ID\n";
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
			case 4:
				sortMode = FieldMode::ADRESSEE_ID;
				break;
			}
			Sort((Entity**&)m_storage->m_dialogueList, size, (OrderMode)order, sortMode);
		}
		else if (command == FILTER)
		{
			std::cout << "Fields for filter\n";
			std::cout << "0. ID\n";
			std::cout << "1. Date\n";
			std::cout << "2. Message\n";
			std::cout << "3. Sender ID\n";
			std::cout << "4. Adressee ID\n";
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
				Filter((Entity**&)m_storage->m_dialogueList, size, id, FieldMode::ID);
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
				Filter((Entity**&)m_storage->m_dialogueList, size, date, FieldMode::DATE);
			}
			if (field == 2)
			{
				std::cout << "Input part of message: ";
				std::string message{};
				std::getline(std::cin, message);
				Filter((Entity**&)m_storage->m_dialogueList, size, message, FieldMode::CONTENT);
			}
			if (field == 3)
			{
				std::cout << "Input part of sender ID: ";
				Id senderId;
				std::cin >> senderId;
				std::cin.ignore();
				Filter((Entity**&)m_storage->m_dialogueList, size, senderId, FieldMode::OWNER_ID);
			}
			if (field == 4)
			{
				std::cout << "Input part of adressee ID: ";
				Id adresseeId;
				std::cin >> adresseeId;
				std::cin.ignore();
				Filter((Entity**&)m_storage->m_dialogueList, size, adresseeId, FieldMode::ADRESSEE_ID);
			}
			m_storage->SetDialogueListSize(size);
		}

		if (command == ADD || command == REMOVE || command == EDIT)
		{
			m_storage->SaveDialogueList();
		}

		system("cls");
	}

	return 0;
}