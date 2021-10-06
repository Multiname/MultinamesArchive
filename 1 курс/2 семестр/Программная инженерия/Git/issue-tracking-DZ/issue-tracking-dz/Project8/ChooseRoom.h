#ifndef CHOOSE_ROOM_H
#define CHOOSE_ROOM_H
#include "RoomStorage.h"
#include "OrderStorage.h"
#include "UserStorage.h"

namespace BlackLine
{
	size_t FindIndex(RoomStorage& roomStorage, unsigned short number);
	std::string FindOrdersWithUsers(RoomStorage& roomStorage,
		OrderStorage& orderStorage,UserStorage& userStorage, size_t index, size_t& numberOfOrders);
	void DeleteOrder(RoomStorage& roomStorage, OrderStorage& orderStorage,
		UserStorage& userStorage, size_t roomIndex, size_t orderNumber);
	bool EditOrder(RoomStorage& roomStorage, OrderStorage& orderStorage, size_t roomIndex, size_t orderNumber,
		unsigned short startDay, unsigned short startMonth, unsigned short startYear,
		unsigned short endDay, unsigned short endMonth, unsigned short endYear);
	short BuyNumber(RoomStorage& roomStorage, OrderStorage& orderStorage, size_t roomIndex, size_t orderNumber,
		unsigned short startDay, unsigned short startMonth, unsigned short startYear,
		unsigned short endDay, unsigned short endMonth, unsigned short endYear, unsigned long userId);
	void EditNumber(RoomStorage& roomStorage, size_t index, unsigned long cost,
		bool wifi, bool television, std::string sleepingPlace, std::string roomSize, bool isAvailable);
}

#endif // !CHOOSE_ROOM_H