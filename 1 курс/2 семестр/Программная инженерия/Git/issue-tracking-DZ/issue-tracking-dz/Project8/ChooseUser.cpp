#include <iostream>
#include "ChooseUser.h"

namespace BlackLine
{
	void ChangeRole(UserStorage& users, size_t index, User::Role role)
	{
		users[index].role = role;
		users.Write();
	}
}