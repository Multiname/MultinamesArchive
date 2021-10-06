#ifndef FILTER_H
#define FILTER_H
#include "GetField.h"

namespace KMK
{
	void Filter(Entity**& entities, size_t& size, Id fieldForSearch, FieldMode mode);
	void Filter(Entity**& entities, size_t& size, std::string fieldForSearch, FieldMode mode);
	void Filter(Entity**& entities, size_t& size, Entity::Date fieldForSearch, FieldMode mode);
}

#endif // !FILTER_H