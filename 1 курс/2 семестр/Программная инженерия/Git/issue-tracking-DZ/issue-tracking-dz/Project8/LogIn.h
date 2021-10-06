#ifndef LOGIN_H
#define LOGIN_H

#include "UserStorage.h"

namespace BlackLine
{
	bool Register(UserStorage& users, std::string fullName,
		std::string login, std::string password);
	unsigned long LogIn(UserStorage& users,
		std::string login, std::string password);
}
#endif // !LOGIN_H