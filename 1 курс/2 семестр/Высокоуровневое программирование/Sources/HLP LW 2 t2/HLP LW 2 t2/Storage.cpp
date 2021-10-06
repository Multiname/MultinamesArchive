#include "Storage.h"
#include <fstream>

namespace KMK
{
	Storage::Storage()
	{
		m_dialogueList = {};
		m_interestList = {};
		m_reminderList = {};
		m_themeList = {};
		m_userList = {};

		m_dialogueListFilePath = {};
		m_interestListFilePath = {};
		m_reminderListFilePath = {};
		m_themeListFilePath = {};
		m_userListFilePath = {};

		m_dialogueListSize = 0;
		m_interestListSize = 0;
		m_reminderListSize = 0;
		m_themeListSize = 0;
		m_userListSize = 0;

		m_dialogueIdCounterFilePath = {};
		m_interestIdCounterFilePath = {};
		m_reminderIdCounterFilePath = {};
		m_themeIdCounterFilePath = {};
		m_userIdCounterFilePath = {};

		m_dialogueIdCounter = {};
		m_interestIdCounter= {};
		m_reminderIdCounter = {};
		m_themeIdCounter = {};
		m_userIdCounter = {};

	}

	Storage::Storage(std::string dialogueListFilePath, std::string interestListFilePath,
		std::string reminderListFilePath, std::string themeListFilePath, std::string userListFilePath,
		std::string dialogueIdCounterFilePath, std::string interestIdCounterFilePath,
		std::string reminderIdCounterFilePath, std::string themeIdCounterFilePath,
		std::string userIdCounterFilePath)
	{
		m_dialogueListFilePath = dialogueListFilePath;
		m_interestListFilePath = interestListFilePath;
		m_reminderListFilePath = reminderListFilePath;
		m_themeListFilePath = themeListFilePath;
		m_userListFilePath = userListFilePath;

		LoadDialogueList();
		LoadInterestList();
		LoadReminderList();
		LoadThemeList();
		LoadUserList();

		m_dialogueIdCounterFilePath = dialogueIdCounterFilePath;
		m_interestIdCounterFilePath = interestIdCounterFilePath;
		m_reminderIdCounterFilePath = reminderIdCounterFilePath;
		m_themeIdCounterFilePath = themeIdCounterFilePath;
		m_userIdCounterFilePath = userIdCounterFilePath;

		m_dialogueIdCounter.SetIdCounter(dialogueIdCounterFilePath);
		m_interestIdCounter.SetIdCounter(interestIdCounterFilePath);
		m_reminderIdCounter.SetIdCounter(reminderIdCounterFilePath);
		m_themeIdCounter.SetIdCounter(themeIdCounterFilePath);
		m_userIdCounter.SetIdCounter(userIdCounterFilePath);
	}

	size_t Storage::GetDialogueListSize() { return m_dialogueListSize; }
	size_t Storage::GetInterestListSize() { return m_interestListSize; }
	size_t Storage::GetReminderListSize() { return m_reminderListSize; }
	size_t Storage::GetThemeListSize() { return m_themeListSize; }
	size_t Storage::GetUserListSize() { return m_userListSize; }

	void Storage::SetDialogueListSize(size_t size) { m_dialogueListSize = size; }
	void Storage::SetInterestListSize(size_t size) { m_interestListSize = size; }
	void Storage::SetReminderListSize(size_t size) { m_reminderListSize = size; }
	void Storage::SetThemeListSize(size_t size) { m_themeListSize = size; }
	void Storage::SetUserListSize(size_t size) { m_userListSize = size; }

	void Storage::SaveDialogueList()
	{
		std::ofstream fileWrite(m_dialogueListFilePath, std::ios::binary);
		fileWrite.write((char*)&m_dialogueListSize, sizeof(size_t));
		for (Iteration i{}; i < m_dialogueListSize; ++i)
		{
			Id id = m_dialogueList[i]->GetId();
			fileWrite.write((char*)&id, sizeof(Id));

			fileWrite.write((char*)&m_dialogueList[i]->GetDate(), sizeof(Entity::Date));

			size_t stringSize = m_dialogueList[i]->GetContent().length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(m_dialogueList[i]->GetContent().c_str(), stringSize);

			id = m_dialogueList[i]->GetOwnerId();
			fileWrite.write((char*)&id, sizeof(Id));

			id = m_dialogueList[i]->GetAdresseeId();
			fileWrite.write((char*)&id, sizeof(Id));
		}
		fileWrite.close();
	}

	void Storage::SaveInterestList()
	{
		std::ofstream fileWrite(m_interestListFilePath, std::ios::binary);
		fileWrite.write((char*)&m_interestListSize, sizeof(size_t));
		for (Iteration i{}; i < m_interestListSize; ++i)
		{
			Id id = m_interestList[i]->GetId();
			fileWrite.write((char*)&id, sizeof(Id));

			fileWrite.write((char*)&m_interestList[i]->GetDate(), sizeof(Entity::Date));

			size_t stringSize = m_interestList[i]->GetContent().length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(m_interestList[i]->GetContent().c_str(), stringSize);

			id = m_interestList[i]->GetOwnerId();
			fileWrite.write((char*)&id, sizeof(Id));
		}
		fileWrite.close();
	}

	void Storage::SaveReminderList()
	{
		std::ofstream fileWrite(m_reminderListFilePath, std::ios::binary);
		fileWrite.write((char*)&m_reminderListSize, sizeof(size_t));
		for (Iteration i{}; i < m_reminderListSize; ++i)
		{
			Id id = m_reminderList[i]->GetId();
			fileWrite.write((char*)&id, sizeof(Id));

			fileWrite.write((char*)&m_reminderList[i]->GetDate(), sizeof(Entity::Date));

			size_t stringSize = m_reminderList[i]->GetContent().length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(m_reminderList[i]->GetContent().c_str(), stringSize);

			id = m_reminderList[i]->GetOwnerId();
			fileWrite.write((char*)&id, sizeof(Id));

			fileWrite.write((char*)&m_reminderList[i]->GetReminderTime(), sizeof(Entity::Date));
		}
		fileWrite.close();
	}

	void Storage::SaveThemeList()
	{
		std::ofstream fileWrite(m_themeListFilePath, std::ios::binary);
		fileWrite.write((char*)&m_themeListSize, sizeof(size_t));
		for (Iteration i{}; i < m_themeListSize; ++i)
		{
			Id id = m_themeList[i]->GetId();
			fileWrite.write((char*)&id, sizeof(Id));

			fileWrite.write((char*)&m_themeList[i]->GetDate(), sizeof(Entity::Date));

			size_t stringSize = m_themeList[i]->GetContent().length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(m_themeList[i]->GetContent().c_str(), stringSize);

			id = m_themeList[i]->GetOwnerId();
			fileWrite.write((char*)&id, sizeof(Id));
		}
		fileWrite.close();
	}

	void Storage::SaveUserList()
	{
		std::ofstream fileWrite(m_userListFilePath, std::ios::binary);
		fileWrite.write((char*)&m_userListSize, sizeof(size_t));
		for (Iteration i{}; i < m_userListSize; ++i)
		{
			Id id = m_userList[i]->GetId();
			fileWrite.write((char*)&id, sizeof(Id));

			fileWrite.write((char*)&m_userList[i]->GetDate(), sizeof(Entity::Date));

			size_t stringSize = m_userList[i]->GetName().length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(m_userList[i]->GetName().c_str(), stringSize);

			stringSize = m_userList[i]->GetLogin().length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(m_userList[i]->GetLogin().c_str(), stringSize);

			stringSize = m_userList[i]->GetPassword().length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(m_userList[i]->GetPassword().c_str(), stringSize);
		}
		fileWrite.close();
	}

	void Storage::LoadDialogueList()
	{
		std::ifstream fileRead(m_dialogueListFilePath, std::ios::binary);
		fileRead.read((char*)&m_dialogueListSize, sizeof(size_t));
		m_dialogueList = new Dialogue * [m_dialogueListSize] {};
		for (Iteration i{}; i < m_dialogueListSize; ++i)
		{
			Id id{};
			fileRead.read((char*)&id, sizeof(Id));

			Entity::Date date{};
			fileRead.read((char*)&date, sizeof(Entity::Date));

			size_t stringSize{};
			fileRead.read((char*)&stringSize, sizeof(size_t));
			char* message = new char[stringSize] {};
			fileRead.read(message, stringSize);

			Id ownerId{};
			fileRead.read((char*)&ownerId, sizeof(Id));

			Id adresseeId{};
			fileRead.read((char*)&adresseeId, sizeof(Id));

			m_dialogueList[i] = new Dialogue{ id, date, message, ownerId, adresseeId };

			delete[] message;
		}
		fileRead.close();
	}

	void Storage::LoadInterestList()
	{
		std::ifstream fileRead(m_interestListFilePath, std::ios::binary);
		fileRead.read((char*)&m_interestListSize, sizeof(size_t));
		m_interestList = new Interest * [m_interestListSize] {};
		for (Iteration i{}; i < m_interestListSize; ++i)
		{
			Id id{};
			fileRead.read((char*)&id, sizeof(Id));

			Entity::Date date{};
			fileRead.read((char*)&date, sizeof(Entity::Date));

			size_t stringSize{};
			fileRead.read((char*)&stringSize, sizeof(size_t));
			char* interest = new char[stringSize] {};
			fileRead.read(interest, stringSize);

			Id ownerId{};
			fileRead.read((char*)&ownerId, sizeof(Id));

			m_interestList[i] = new Interest{ id, date, interest, ownerId };

			delete[] interest;
		}
		fileRead.close();
	}

	void Storage::LoadReminderList()
	{
		std::ifstream fileRead(m_reminderListFilePath, std::ios::binary);
		fileRead.read((char*)&m_reminderListSize, sizeof(size_t));
		m_reminderList = new Reminder * [m_reminderListSize] {};
		for (Iteration i{}; i < m_reminderListSize; ++i)
		{
			Id id{};
			fileRead.read((char*)&id, sizeof(Id));

			Entity::Date date{};
			fileRead.read((char*)&date, sizeof(Entity::Date));

			size_t stringSize{};
			fileRead.read((char*)&stringSize, sizeof(size_t));
			char* reminder = new char[stringSize] {};
			fileRead.read(reminder, stringSize);

			Id ownerId{};
			fileRead.read((char*)&ownerId, sizeof(Id));

			Entity::Date reminderDate{};
			fileRead.read((char*)&reminderDate, sizeof(Entity::Date));

			m_reminderList[i] = new Reminder{ id, date, reminder, ownerId, reminderDate };

			delete[] reminder;
		}
		fileRead.close();
	}

	void Storage::LoadThemeList()
	{
		std::ifstream fileRead(m_themeListFilePath, std::ios::binary);
		fileRead.read((char*)&m_themeListSize, sizeof(size_t));
		m_themeList = new Theme * [m_themeListSize] {};
		for (Iteration i{}; i < m_themeListSize; ++i)
		{
			Id id{};
			fileRead.read((char*)&id, sizeof(Id));

			Entity::Date date{};
			fileRead.read((char*)&date, sizeof(Entity::Date));

			size_t stringSize{};
			fileRead.read((char*)&stringSize, sizeof(size_t));
			char* theme = new char[stringSize] {};
			fileRead.read(theme, stringSize);

			Id ownerId{};
			fileRead.read((char*)&ownerId, sizeof(Id));

			m_themeList[i] = new Theme{ id, date, theme, ownerId };

			delete[] theme;
		}
		fileRead.close();
	}

	void Storage::LoadUserList()
	{
		std::ifstream fileRead(m_userListFilePath, std::ios::binary);
		fileRead.read((char*)&m_userListSize, sizeof(size_t));
		m_userList = new User * [m_userListSize] {};
		for (Iteration i{}; i < m_userListSize; ++i)
		{
			Id id{};
			fileRead.read((char*)&id, sizeof(Id));

			Entity::Date date{};
			fileRead.read((char*)&date, sizeof(Entity::Date));

			size_t stringSize{};
			fileRead.read((char*)&stringSize, sizeof(size_t));
			char* name = new char[stringSize] {};
			fileRead.read(name, stringSize);

			fileRead.read((char*)&stringSize, sizeof(size_t));
			char* login = new char[stringSize] {};
			fileRead.read(login, stringSize);

			fileRead.read((char*)&stringSize, sizeof(size_t));
			char* password = new char[stringSize] {};
			fileRead.read(password, stringSize);

			m_userList[i] = new User{ id, date, name, login, password };

			delete[] name;
			delete[] login;
			delete[] password;
		}
		fileRead.close();
	}

	Id Storage::GetNextDialogueId() { return m_dialogueIdCounter(); }
	Id Storage::GetNextInterestId() { return m_interestIdCounter(); }
	Id Storage::GetNextReminderId() { return m_reminderIdCounter(); }
	Id Storage::GetNextThemeId() { return m_themeIdCounter(); }
	Id Storage::GetNextUserId() { return m_userIdCounter(); }
}