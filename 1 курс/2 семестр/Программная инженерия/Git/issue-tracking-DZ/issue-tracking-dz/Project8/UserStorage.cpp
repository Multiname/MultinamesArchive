#include "UserStorage.h"
#include <fstream>

namespace BlackLine
{
	UserStorage::UserStorage() : m_idCounter()
	{
		m_path = {};
		m_userList = {};

		if (m_userList.size() == 0)
		{
			m_userList.push_back({ User::Role::ADMIN, GetNextId(), "ADMIN", "admin", "admin" });
			Write();
		}
	}

	UserStorage::UserStorage(std::string path, std::string idCounter) : m_idCounter(idCounter)
	{
		m_path = path;
		Read();

		if (m_userList.size() == 0)
		{
			m_userList.push_back({ User::Role::ADMIN, GetNextId(), "ADMIN", "admin", "admin" });
			Write();
		}
	}

	void UserStorage::Write()
	{
		std::ofstream fileWrite(m_path, std::ios::binary);

		size_t size = m_userList.size();
		fileWrite.write((char*)&size, sizeof(size_t));

		std::vector <User>::const_iterator it = m_userList.begin();
		while (it != m_userList.end())
		{
			fileWrite.write((char*)&it->role, sizeof(User::Role));
			fileWrite.write((char*)&it->id, sizeof(unsigned long));

			size_t stringSize = it->fullName.length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(it->fullName.c_str(), stringSize);

			stringSize = it->login.length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(it->login.c_str(), stringSize);

			stringSize = it->password.length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(it->password.c_str(), stringSize);

			++it;
		}

		fileWrite.close();
	}

	void UserStorage::Read()
	{
		std::ifstream fileRead(m_path, std::ios::binary);

		size_t size{};
		fileRead.read((char*)&size, sizeof(size_t));

		for (size_t i{}; i < size; ++i)
		{
			User user{};
			fileRead.read((char*)&user.role, sizeof(User::Role));
			fileRead.read((char*)&user.id, sizeof(unsigned long));

			size_t stringSize{};
			fileRead.read((char*)&stringSize, sizeof(size_t));
			char* str = new char[stringSize] {};
			fileRead.read(str, stringSize);
			user.fullName = str;
			delete[] str;

			fileRead.read((char*)&stringSize, sizeof(size_t));
			str = new char[stringSize] {};
			fileRead.read(str, stringSize);
			user.login = str;
			delete[] str;

			fileRead.read((char*)&stringSize, sizeof(size_t));
			str = new char[stringSize] {};
			fileRead.read(str, stringSize);
			user.password = str;
			delete[] str;

			m_userList.push_back(user);
		}

		fileRead.close();
	}

	void UserStorage::Add(User user)
	{
		m_userList.push_back(user);
		Write();
	}

	void UserStorage::Remove(size_t index)
	{
		m_userList.erase(m_userList.begin() + index);
		Write();
	}

	unsigned long UserStorage::GetNextId() { return m_idCounter(); }
	size_t UserStorage::GetSize() { return m_userList.size(); }

	User& UserStorage::operator[](size_t index) { return m_userList[index]; }
}