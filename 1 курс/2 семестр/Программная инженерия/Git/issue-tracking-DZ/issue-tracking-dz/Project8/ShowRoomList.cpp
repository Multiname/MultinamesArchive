#include "ShowRoomList.h"

namespace BlackLine
{
	std::string ShowRoomList(RoomStorage roomStorage,
		OrderStorage orderStorage, bool viewTemporarilyUnavailable)
	{
		std::string text{};
		for (size_t i{}; i < roomStorage.GetSize(); ++i)
		{
			if (roomStorage[i].isAvailable)
			{
				text += "Номер ";
				text += std::to_string(roomStorage[i].number);
				text += "\n";
				for (size_t j{}; j < orderStorage.GetSize(); ++j)
				{
					if (roomStorage[i].id == orderStorage[j].roomId)
					{
						text += "   ";
						text += std::to_string(orderStorage[j].startDate.day);
						text += "/";
						text += std::to_string(orderStorage[j].startDate.month);
						text += "/";
						text += std::to_string(orderStorage[j].startDate.year);
						text += " - ";
						text += std::to_string(orderStorage[j].endDate.day);
						text += "/";
						text += std::to_string(orderStorage[j].endDate.month);
						text += "/";
						text += std::to_string(orderStorage[j].endDate.year);
						text += "\n";
					}
				}
				text += "\n";
			}
			else if (viewTemporarilyUnavailable)
			{
				text += "Номер ";
				text += std::to_string(roomStorage[i].number);
				text += "\n   Временно недоступно\n\n";
			}
		}

		return text;
	}
}