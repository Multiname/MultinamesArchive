#ifndef USER_H
#define USER_H
#include "Entity.h"
#include <string>

namespace KMK
{
	class User : public Entity
	{
	public:
		User();
		User(Id id, Date date, std::string name, std::string login, std::string password);
		User(User* user);
		virtual ~User() {}

		std::string GetName();
		std::string GetLogin();
		std::string GetPassword();

		void SetName(std::string name);
		void SetLogin(std::string login);
		void SetPassword(std::string password);

	private:
		std::string m_name{};
		std::string m_login{};
		std::string m_password{};
	};
}

#endif // !USER_H