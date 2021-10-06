#ifndef EDIT_ROOM_LIST_H
#define EDIT_ROOM_LIST_H
#include "RoomStorage.h"

namespace BlackLine
{
	unsigned long AddRoom(RoomStorage& roomStorage, unsigned short number, unsigned long cost,
		bool wifi, bool television, std::string sleepingPlace, std::string roomSize);
	void DeleteRoom(RoomStorage& roomStorage, unsigned short number);
}

#endif // !EDIT_ROOM_LIST_H