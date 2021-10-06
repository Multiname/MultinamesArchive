#include "EditRoomList.h"

namespace BlackLine
{
	unsigned long AddRoom(RoomStorage& roomStorage, unsigned short number, unsigned long cost,
		bool wifi, bool television, std::string sleepingPlace, std::string roomSize)
	{
		Room newRoom{};
		newRoom.id = roomStorage.GetNextId();
		newRoom.number = number;
		newRoom.cost = cost;
		newRoom.description.wifi = wifi;
		newRoom.description.television = television;
		newRoom.description.sleepingPlace = sleepingPlace;
		newRoom.description.roomSize = roomSize;
		newRoom.isAvailable = true;

		roomStorage.Add(newRoom);
		return newRoom.id;
	}

	void DeleteRoom(RoomStorage& roomStorage, unsigned short number)
	{
		for (size_t i{}; i < roomStorage.GetSize(); ++i)
		{
			if (roomStorage[i].number == number)
			{
				roomStorage.Remove(i);
				break;
			}
		}
	}
}