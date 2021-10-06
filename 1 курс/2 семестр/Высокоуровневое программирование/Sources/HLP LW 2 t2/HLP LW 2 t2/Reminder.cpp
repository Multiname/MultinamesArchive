#include "Reminder.h"

using namespace KMK;

Reminder::Reminder(Id id, Date date, std::string reminder, Id ownerId, Date reminderTime) :
	TextEntity(id, date, reminder, ownerId)
{
	m_reminderTime = reminderTime;
}

Reminder::Reminder(Reminder* reminder) :
	TextEntity(reminder->GetId(), reminder->GetDate(), reminder->GetContent(), reminder->GetOwnerId())
{
	m_reminderTime = reminder->m_reminderTime;
}

Reminder::Date Reminder::GetReminderTime() { return m_reminderTime; }

void Reminder::SetReminderTime(Date reminderTime)
{
	m_reminderTime.day = reminderTime.day;
	m_reminderTime.month = reminderTime.month;
	m_reminderTime.year = reminderTime.year;
}