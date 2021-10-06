#include "ChooseRoom.h"
#include "RemoveOrders.h"
#include "IsFirstLaterThanSecond.h"
#include <Windows.h>

namespace BlackLine
{
	size_t FindIndex(RoomStorage& roomStorage, unsigned short number)
	{
		size_t index = -1;
		for (size_t i{}; i < roomStorage.GetSize(); ++i)
		{
			if (number == roomStorage[i].number)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	std::string FindOrdersWithUsers(RoomStorage& roomStorage, OrderStorage& orderStorage,
		UserStorage& userStorage, size_t index, size_t& numberOfOrders)
	{
		std::string temp{};
		size_t number = 1;

		for (size_t i{}; i < orderStorage.GetSize(); ++i)
		{
			if (roomStorage[index].id == orderStorage[i].roomId)
			{
				for (size_t j{}; j < userStorage.GetSize(); ++j)
				{
					if (orderStorage[i].clientId == userStorage[j].id)
					{
						temp += std::to_string(number);
						temp += ".   ";
						temp += std::to_string(orderStorage[i].startDate.day);
						temp += "/";
						temp += std::to_string(orderStorage[i].startDate.month);
						temp += "/";
						temp += std::to_string(orderStorage[i].startDate.year);
						temp += " - ";
						temp += std::to_string(orderStorage[i].endDate.day);
						temp += "/";
						temp += std::to_string(orderStorage[i].endDate.month);
						temp += "/";
						temp += std::to_string(orderStorage[i].endDate.year);
						temp += ": ";
						temp += userStorage[j].fullName;
						temp += "\n";

						++number;
						break;
					}
				}
			}
		}

		numberOfOrders = number - 1;
		return temp;
	}

	void DeleteOrder(RoomStorage& roomStorage, OrderStorage& orderStorage,
		UserStorage& userStorage, size_t roomIndex, size_t orderNumber)
	{
		size_t currentNumber = 0;
		for (size_t i{}; i < orderStorage.GetSize(); ++i)
		{
			if (roomStorage[roomIndex].id == orderStorage[i].roomId)
			{
				++currentNumber;
				if (currentNumber == orderNumber)
				{
					RemoveDeletedOrder(orderStorage, userStorage,
						"Orders log.txt", i, roomStorage[roomIndex].number);
					break;
				}
			}
		}
	}

	bool EditOrder(RoomStorage& roomStorage, OrderStorage& orderStorage, size_t roomIndex, size_t orderNumber,
		unsigned short startDay, unsigned short startMonth, unsigned short startYear,
		unsigned short endDay, unsigned short endMonth, unsigned short endYear)
	{
		Order::Date StartDate{ startDay, startMonth, startYear };
		Order::Date EndDate{ endDay, endMonth, endYear };

		if (IsFirstLaterThanSecond(EndDate, StartDate)) { return false; }

		size_t currentNumber = 0;
		for (size_t i{}; i < orderStorage.GetSize(); ++i)
		{
			if (roomStorage[roomIndex].id == orderStorage[i].roomId)
			{
				++currentNumber;
				if (currentNumber == orderNumber)
				{
					orderStorage[i].startDate = StartDate;
					orderStorage[i].endDate = EndDate;
					break;
				}
			}
		}

		orderStorage.Sort();
		orderStorage.Write();

		return true;
	}

	short BuyNumber(RoomStorage& roomStorage, OrderStorage& orderStorage, size_t roomIndex, size_t orderNumber,
		unsigned short startDay, unsigned short startMonth, unsigned short startYear,
		unsigned short endDay, unsigned short endMonth, unsigned short endYear, unsigned long userId)
	{
		Order::Date newOrderStartDate{ startDay, startMonth, startYear };
		Order::Date newOrderEndDate{ endDay, endMonth, endYear };

		if (IsFirstLaterThanSecond(newOrderEndDate, newOrderStartDate)) { return 1; }

		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		Order::Date currentDate{ systemTime.wDay, systemTime.wMonth, systemTime.wYear };

		if (IsFirstLaterThanSecond(newOrderStartDate, currentDate)) { return 2; }

		for (size_t j{}; j < orderStorage.GetSize(); ++j)
		{
			if (roomStorage[roomIndex].id == orderStorage[j].roomId)
			{
				if (!(IsFirstLaterThanSecond(newOrderEndDate, orderStorage[j].startDate) ||
					IsFirstLaterThanSecond(orderStorage[j].endDate, newOrderStartDate)))
				{
					return 3;
				}

			}
		}

		orderStorage.Add({ orderStorage.GetNextId(), userId, roomStorage[roomIndex].id,
			{startDay, startMonth, startYear}, {endDay, endMonth, startYear} });
		return 0;
	}

	void EditNumber(RoomStorage& roomStorage, size_t index, unsigned long cost, 
		bool wifi, bool television, std::string sleepingPlace, std::string roomSize, bool isAvailable)
	{
		roomStorage[index].cost = cost;
		roomStorage[index].description.wifi = wifi;
		roomStorage[index].description.television = television;
		roomStorage[index].description.sleepingPlace = sleepingPlace;
		roomStorage[index].description.roomSize = roomSize;
		roomStorage[index].isAvailable = isAvailable;
		roomStorage.Write();
	}
}