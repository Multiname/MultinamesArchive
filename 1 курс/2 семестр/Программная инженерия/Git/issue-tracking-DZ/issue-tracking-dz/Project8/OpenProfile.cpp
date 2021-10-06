#include "OpenProfile.h"
#include "RemoveOrders.h"

namespace BlackLine
{
	std::vector<std::string> ShowOrders(OrderStorage& orderStorage,
		RoomStorage& roomStorage, unsigned long userId)
	{
		std::vector<std::string> orders{};
		for (size_t i = 0; i < orderStorage.GetSize(); i++)
		{
			if (orderStorage[i].clientId == userId)
			{
				std::string text{};
				text += "Номер: ";

				for (size_t j = 0; j < roomStorage.GetSize(); ++j)
				{
					if (orderStorage[i].roomId == roomStorage[j].id)
					{
						text += std::to_string(roomStorage[j].number);
						break;
					}
				}

				text += ";   Время: ";
				text += std::to_string(orderStorage[i].startDate.day);
				text += "/";
				text += std::to_string(orderStorage[i].startDate.month);
				text += "/";
				text += std::to_string(orderStorage[i].startDate.year);
				text += " - ";
				text += std::to_string(orderStorage[i].endDate.day);
				text += "/";
				text += std::to_string(orderStorage[i].endDate.month);
				text += "/";
				text += std::to_string(orderStorage[i].endDate.year);

				orders.push_back(text);
			}
		}

		return orders;
	}

	void CancelOrder(OrderStorage& orderStorage, RoomStorage& roomStorage,
		UserStorage& userStorage, unsigned long userId, size_t index)
	{
		size_t currentIndex = -1;
		for (size_t i = 0; i < orderStorage.GetSize(); i++)
		{
			if (orderStorage[i].clientId == userId)
			{
				++currentIndex;
				if (currentIndex == index)
				{
					RemoveCancelledOrder(orderStorage, roomStorage,
						userStorage, "Orders log.txt", i);
					break;
				}
			}
		}
	}
}