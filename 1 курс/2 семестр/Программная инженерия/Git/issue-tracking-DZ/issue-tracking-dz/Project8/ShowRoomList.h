#ifndef SHOW_ROOM_LIST_H
#define SHOW_ROOM_LIST_H
#include "RoomStorage.h"
#include "OrderStorage.h"

namespace BlackLine
{
	std::string ShowRoomList(RoomStorage roomStorage,
		OrderStorage orderStorage, bool viewTemporarilyUnavailable);
}

#endif // !SHOW_ROOM_LIST_H