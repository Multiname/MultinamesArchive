#ifndef SHOW_USER_LIST_H
#define SHOW_USER_LIST_H
#include "UserStorage.h"
#include "OrderStorage.h"
#include "RoomStorage.h"

namespace BlackLine
{
	std::vector<std::string> ShowUserList(UserStorage& users,
		OrderStorage& orders, RoomStorage& rooms);
}
#endif // !SHOW_USER_LIST_H