#ifndef OPEN_PROFILE_H
#define OPEN_PROFILE_H
#include "OrderStorage.h"
#include "RoomStorage.h"
#include "UserStorage.h"

namespace BlackLine
{
	std::vector<std::string> ShowOrders(OrderStorage& orderStorage,
		RoomStorage& roomStorage, unsigned long userId);
	void CancelOrder(OrderStorage& orderStorage, RoomStorage& roomStorage,
		UserStorage& userStorage, unsigned long userId, size_t index);
}

#endif // !OPEN_PROFILE_H