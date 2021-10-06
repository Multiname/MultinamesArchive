#include "RemoveOrders.h"
#include <Windows.h>
#include "IsFirstLaterThanSecond.h"
#include <fstream>

namespace BlackLine
{
	void RemoveOutdatedOrders(OrderStorage& orderStorage, RoomStorage& roomStorage,
		UserStorage& userStorage,std::string logPath)
	{
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		Order::Date currentDate{ systemTime.wDay, systemTime.wMonth, systemTime.wYear };

		std::ofstream logWrite(logPath, std::ios::app);

		std::vector<size_t> indexesToRemove{};

		for (size_t i{}; i < orderStorage.GetSize(); ++i)
		{
			if (IsFirstLaterThanSecond(orderStorage[i].endDate, currentDate))
			{
				std::string text{};

				text = "[";
				text += std::to_string(currentDate.day);
				text += ":";
				text += std::to_string(currentDate.month);
				text += ":";
				text += std::to_string(currentDate.year);
				text += "]   ";

				text += "Order: ";
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

				text += "   Number: ";
				for (size_t j{}; j < roomStorage.GetSize(); ++j)
				{
					if (orderStorage[i].roomId == roomStorage[j].id)
					{
						text += std::to_string(roomStorage[j].number);
						break;
					}
				}

				text += "   Owner: ";
				for (size_t j{}; j < userStorage.GetSize(); ++j)
				{
					if (orderStorage[i].clientId == userStorage[j].id)
					{
						text += userStorage[j].fullName;
						break;
					}
				}

				text += "   Removal reason: outdated\n";

				logWrite << text;

				indexesToRemove.push_back(i);
			}
		}

		for (size_t i{}; i < indexesToRemove.size(); ++i)
		{
			orderStorage.Remove(indexesToRemove[indexesToRemove.size() - 1 - i]);
		}

		logWrite.close();
	}

	void RemoveCancelledOrder(OrderStorage& orderStorage, RoomStorage& roomStorage,
		UserStorage& userStorage, std::string logPath, size_t index)
	{
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		Order::Date currentDate{ systemTime.wDay, systemTime.wMonth, systemTime.wYear };

		std::ofstream logWrite(logPath, std::ios::app);

		std::string text{};

		text = "[";
		text += std::to_string(currentDate.day);
		text += ":";
		text += std::to_string(currentDate.month);
		text += ":";
		text += std::to_string(currentDate.year);
		text += "]   ";

		text += "Order: ";
		text += std::to_string(orderStorage[index].startDate.day);
		text += "/";
		text += std::to_string(orderStorage[index].startDate.month);
		text += "/";
		text += std::to_string(orderStorage[index].startDate.year);
		text += " - ";
		text += std::to_string(orderStorage[index].endDate.day);
		text += "/";
		text += std::to_string(orderStorage[index].endDate.month);
		text += "/";
		text += std::to_string(orderStorage[index].endDate.year);

		text += "   Number: ";
		for (size_t j{}; j < roomStorage.GetSize(); ++j)
		{
			if (orderStorage[index].roomId == roomStorage[j].id)
			{
				text += std::to_string(roomStorage[j].number);
				break;
			}
		}

		text += "   Owner: ";
		for (size_t j{}; j < userStorage.GetSize(); ++j)
		{
			if (orderStorage[index].clientId == userStorage[j].id)
			{
				text += userStorage[j].fullName;
				break;
			}
		}

		text += "   Removal reason: cancelled by client\n";

		logWrite << text;

		orderStorage.Remove(index);

		logWrite.close();
	}

	void RemoveDeletedOrder(OrderStorage& orderStorage, UserStorage& userStorage,
		std::string logPath, size_t orderIndex, unsigned short roomNumber)
	{
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		Order::Date currentDate{ systemTime.wDay, systemTime.wMonth, systemTime.wYear };

		std::ofstream logWrite(logPath, std::ios::app);

		std::string text{};

		text = "[";
		text += std::to_string(currentDate.day);
		text += ":";
		text += std::to_string(currentDate.month);
		text += ":";
		text += std::to_string(currentDate.year);
		text += "]   ";

		text += "Order: ";
		text += std::to_string(orderStorage[orderIndex].startDate.day);
		text += "/";
		text += std::to_string(orderStorage[orderIndex].startDate.month);
		text += "/";
		text += std::to_string(orderStorage[orderIndex].startDate.year);
		text += " - ";
		text += std::to_string(orderStorage[orderIndex].endDate.day);
		text += "/";
		text += std::to_string(orderStorage[orderIndex].endDate.month);
		text += "/";
		text += std::to_string(orderStorage[orderIndex].endDate.year);

		text += "   Number: ";
		text += std::to_string(roomNumber);

		text += "   Owner: ";
		for (size_t j{}; j < userStorage.GetSize(); ++j)
		{
			if (orderStorage[orderIndex].clientId == userStorage[j].id)
			{
				text += userStorage[j].fullName;
				break;
			}
		}

		text += "   Removal reason: deleted by admin\n";

		logWrite << text;
		
		orderStorage.Remove(orderIndex);

		logWrite.close();
	}
}