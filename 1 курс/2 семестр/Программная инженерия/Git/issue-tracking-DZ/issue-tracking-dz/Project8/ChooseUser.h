#ifndef CHOOSE_USER_H
#define CHOOSE_USER_H

#include "UserStorage.h"

namespace BlackLine
{
	void ChangeRole(UserStorage& users, size_t index, User::Role role);
}

#endif // !CHOOSE_USER_H