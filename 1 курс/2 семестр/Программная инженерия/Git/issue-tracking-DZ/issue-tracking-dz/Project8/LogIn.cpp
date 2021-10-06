#include "LogIn.h"

namespace BlackLine
{
	bool Register(UserStorage &users, std::string fullName,
		std::string login, std::string password)
	{
		User newUser;

		newUser.role = User::CLIENT;

		for (size_t i{}; i < users.GetSize(); ++i)
		{
			if (login == users[i].login)
			{
				return false;
			}
		}

		newUser.fullName = fullName;
		newUser.login = login;
		newUser.password = password;
		newUser.id = users.GetNextId();

		users.Add(newUser);

		return true;
	}

	unsigned long LogIn(UserStorage& users,
		std::string login, std::string password)
	{
		for (size_t i = 0; i < users.GetSize(); ++i)
		{
			if (login == users[i].login && password == users[i].password)
			{
				return users[i].id;
			}
		}

		return 0;
	}
}