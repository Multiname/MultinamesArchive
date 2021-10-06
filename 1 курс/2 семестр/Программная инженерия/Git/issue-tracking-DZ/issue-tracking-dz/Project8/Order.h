#ifndef ORDER_H
#define ORDER_H

struct Order
{
	unsigned long id{};
	unsigned long clientId{};
	unsigned long roomId{};

	struct Date
	{
		unsigned short day{};
		unsigned short month{};
		unsigned short year{};
	};

	Date startDate{};
	Date endDate{};
};

#endif // !ORDER_H