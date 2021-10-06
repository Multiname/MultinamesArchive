#include "IsFirstLaterThanSecond.h"

namespace BlackLine
{
	bool IsFirstLaterThanSecond(Order::Date firstDate, Order::Date secondDate)
	{
		return firstDate.day + firstDate.month * 100 + firstDate.year * 10000 <
			secondDate.day + secondDate.month * 100 + secondDate.year * 10000;
	}
}