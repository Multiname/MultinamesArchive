#ifndef REMOVE_ORDERS_H
#define REMOVE_ORDERS_H
#include "OrderStorage.h"
#include "RoomStorage.h"
#include "UserStorage.h"

namespace BlackLine
{
	void RemoveOutdatedOrders(OrderStorage& orderStorage, RoomStorage& roomStorage,
		UserStorage& userStorage, std::string logPath);
	void RemoveCancelledOrder(OrderStorage& orderStorage, RoomStorage& roomStorage,
		UserStorage& userStorage, std::string logPath, size_t index);
	void RemoveDeletedOrder(OrderStorage& orderStorage, UserStorage& userStorage,
		std::string logPath, size_t orderIndex, unsigned short roomNumber);
}

#endif // !REMOVE_ORDERS_H