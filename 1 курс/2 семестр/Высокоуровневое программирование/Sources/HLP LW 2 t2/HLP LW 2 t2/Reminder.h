#ifndef REMINDER_H
#define REMINDER_H
#include "TextEntity.h"

namespace KMK
{
	class Reminder : public TextEntity
	{
	public:
		Reminder(Id id, Date date, std::string reminder, Id ownerId, Date reminderTime);
		Reminder(Reminder* reminder);
		virtual ~Reminder() {}

		Date GetReminderTime();

		void SetReminderTime(Date reminderTime);

	private:
		Date m_reminderTime{};
	};
}

#endif // !REMINDER_H