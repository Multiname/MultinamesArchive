#ifndef FILTER_ROOM_LIST_H
#define FILTER_ROOM_LIST_H
#include "ShowRoomList.h"

namespace BlackLine
{
	std::string FilterRoomList(RoomStorage roomStorage, OrderStorage orderStorage,
		unsigned short startDay, unsigned short startMonth, unsigned short startYear,
		unsigned short endDay, unsigned short endMonth, unsigned short endYear);
}

#endif // !FILTER_ROOM_LIST_H