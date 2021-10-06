#ifndef USER_H
#define USER_H

#include <string>

namespace BlackLine
{
	struct User
	{
		enum Role
		{
			CLIENT,
			ADMIN,
			BANNED
		};
		Role role{};

		unsigned long id{};
		std::string fullName{};
		std::string login{};
		std::string password{};
	};
}

#endif // !USER_H