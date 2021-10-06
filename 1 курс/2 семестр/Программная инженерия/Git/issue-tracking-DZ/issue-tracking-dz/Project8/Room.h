#ifndef ROOM_H
#define ROOM_H

#include <string>

namespace BlackLine
{
	struct Room
	{
		unsigned long id{};
		unsigned short number{};
		unsigned long cost{};

		struct Description
		{
			bool wifi{};
			bool television{};
			std::string sleepingPlace{};
			std::string roomSize{};
		};

		Description description{};

		bool isAvailable{};
	};
}

#endif // !ROOM_H