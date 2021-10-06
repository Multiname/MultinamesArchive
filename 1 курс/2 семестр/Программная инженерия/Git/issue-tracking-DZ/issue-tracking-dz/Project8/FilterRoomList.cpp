#include "FilterRoomList.h"
#include <iostream>
#include "IsFirstLaterThanSecond.h"
#include <Windows.h>

namespace BlackLine
{
	std::string FilterRoomList(RoomStorage roomStorage, OrderStorage orderStorage,
		unsigned short startDay, unsigned short startMonth, unsigned short startYear,
		unsigned short endDay, unsigned short endMonth, unsigned short endYear)
	{
		setlocale(LC_ALL, "Russian");

		Order::Date startDate{ startDay, startMonth, startYear };
		Order::Date endDate{ endDay, endMonth, endYear };

		if (IsFirstLaterThanSecond(endDate, startDate)) { return "Невозможная дата"; }

		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		Order::Date currentDate{ systemTime.wDay, systemTime.wMonth, systemTime.wYear };

		if (IsFirstLaterThanSecond(startDate, currentDate)) { return "Устаревший заказ"; }

		std::string temp{};
		
		for (size_t i{}; i < roomStorage.GetSize(); ++i)
		{
			if (roomStorage[i].isAvailable)
			{
				bool available = true;
				for (size_t j{}; j < orderStorage.GetSize(); ++j)
				{
					if (roomStorage[i].id == orderStorage[j].roomId)
					{
						if (!(IsFirstLaterThanSecond(endDate, orderStorage[j].startDate) ||
							IsFirstLaterThanSecond(orderStorage[j].endDate, startDate)))
						{
							available = false;
							break;
						}
					}
				}

				if (available)
				{
					temp += std::to_string(roomStorage[i].number);
					temp += " ";
				}
			}
		}

		return temp;
	}
}