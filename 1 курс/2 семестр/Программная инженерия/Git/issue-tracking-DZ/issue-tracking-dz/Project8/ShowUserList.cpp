#include "ShowUserList.h"
#include <set>

namespace BlackLine
{
	std::vector<std::string> ShowUserList(UserStorage& users,
		OrderStorage& orders, RoomStorage& rooms)
	{
		std::vector<std::string> temp{};
		for (size_t i = 0; i < users.GetSize() ; ++i)
		{
			std::string text{};

			text += "Имя: ";
			text += users[i].fullName;
			text += ";   Логин: ";
			text += users[i].login;

			if (users[i].role != BlackLine::User::ADMIN)
			{
				text += ";   Номера: ";
				std::set<unsigned short> bookedNumbers{};
				for (size_t j{}; j < orders.GetSize(); ++j)
				{
					if (orders[j].clientId == users[i].id)
					{
						for (size_t k{}; k < rooms.GetSize(); ++k)
						{
							if (rooms[k].id == orders[j].roomId)
							{
								bookedNumbers.insert(rooms[k].number);
								break;
							}
						}
					}
				}

				for (std::set<unsigned short>::iterator it = bookedNumbers.begin(); it != bookedNumbers.end(); ++it)
				{
					text += std::to_string(*it);
					text += " ";
				}
			}

			temp.push_back(text);
		}

		return temp;
	}
}