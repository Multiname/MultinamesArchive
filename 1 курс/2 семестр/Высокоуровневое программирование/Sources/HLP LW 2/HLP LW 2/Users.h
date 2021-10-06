#ifndef USERS_H
#define USERS_H
#include "AbstractItemMenu.h"
#include "NewUser.h"
#include "Format.h"
#include "User.h"

namespace KMK
{
	class Users : public ItemMenu
	{
	public:
		Users(char* item_name, ItemMenu* users, size_t numOfUsers, ItemMenu* newUser, ItemMenu* format);

		char* GetItemName();
		void PrintItemName();
		int run();

	private:
		ItemMenu* m_users;
		size_t m_numOfUsers;
		ItemMenu* m_newUser;
		ItemMenu* m_format;
	};
}

#endif // !USERS_H