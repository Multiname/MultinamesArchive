#ifndef REMINDER_LIST_ITEM_H
#define REMINDER_LIST_ITEM_H
#include "AbstractMenuItem.h"
#include "Reminder.h"
#include "Storage.h"

namespace KMK
{
	class ReminderListItem : public MenuItem
	{
	public:
		ReminderListItem(std::string itemName, Storage* storage);

		int Run();

	private:
		Storage* m_storage{};
	};
}

#endif // !REMINDER_LIST_ITEM_H