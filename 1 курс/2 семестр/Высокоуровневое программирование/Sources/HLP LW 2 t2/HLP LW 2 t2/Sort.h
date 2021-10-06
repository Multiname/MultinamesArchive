#ifndef SORT_H
#define SORT_H
#include "GetField.h"

namespace KMK
{
	enum class OrderMode
	{
		DESCENDING,
		ASCENDING
	};

	void Sort(Entity**& entities, size_t size, OrderMode order, FieldMode mode);
}

#endif // !SORT_H