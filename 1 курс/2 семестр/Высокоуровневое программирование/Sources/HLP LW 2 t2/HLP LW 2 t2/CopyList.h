#ifndef COPY_LIST_H
#define COPY_LIST_H
#include "Dialogue.h"
#include "Interest.h"
#include "Reminder.h"
#include "Theme.h"
#include "User.h"

namespace KMK
{
	Dialogue** CopyList(Dialogue** list, size_t size);
	Interest** CopyList(Interest** list, size_t size);
	Reminder** CopyList(Reminder** list, size_t size);
	Theme** CopyList(Theme** list, size_t size);
	User** CopyList(User** list, size_t size);
}

#endif // !COPY_LIST_H