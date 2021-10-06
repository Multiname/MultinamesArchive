#ifndef EDIT_H
#define EDIT_H
#include "GetField.h"

namespace KMK
{
	void Edit(Entity**& entities, size_t size, Id idToEdit, void* newField, FieldMode mode);
}

#endif // !EDIT_H