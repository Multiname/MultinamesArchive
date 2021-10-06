#include "User.h"
#include <iostream>

using namespace KMK;

User::User() : Entity(0, {})
{
	m_name = {};
	m_login = {};
	m_password = {};
}

User::User(Id id, Date date, std::string name, std::string login, std::string password) :
	Entity(id, date)
{
	m_name = name;
	m_login = login;
	m_password = password;
}

User::User(User* user) : Entity(user->GetId(), user->GetDate())
{
	m_name = user->m_name;
	m_login = user->m_login;
	m_password = user->m_password;
}

std::string User::GetName() { return m_name; }
std::string User::GetLogin() { return m_login; }
std::string User::GetPassword() { return m_password; }

void User::SetName(std::string name) {m_name = name; }
void User::SetLogin(std::string login) { m_login = login; }
void User::SetPassword(std::string password) { m_password = password; }