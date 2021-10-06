#ifndef STORAGE_H
#define STORAGE_H
#include "Dialogue.h"
#include "Interest.h"
#include "Reminder.h"
#include "Theme.h"
#include "User.h"
#include "IdCounter.h"

namespace KMK
{
	class Storage
	{
	public:
		Storage();
		Storage(std::string dialogueListFilePath, std::string interestListFilePath,
			std::string reminderListFilePath, std::string themeListFilePath, std::string userListFilePath,
			std::string dialogueIdCounterFilePath, std::string interestIdCounterFilePath,
			std::string reminderIdCounterFilePath, std::string themeIdCounterFilePath,
			std::string userIdCounterFilePath);

		size_t GetDialogueListSize();
		size_t GetInterestListSize();
		size_t GetReminderListSize();
		size_t GetThemeListSize();
		size_t GetUserListSize();

		void SetDialogueListSize(size_t size);
		void SetInterestListSize(size_t size);
		void SetReminderListSize(size_t size);
		void SetThemeListSize(size_t size);
		void SetUserListSize(size_t size);

		void SaveDialogueList();
		void SaveInterestList();
		void SaveReminderList();
		void SaveThemeList();
		void SaveUserList();

		void LoadDialogueList();
		void LoadInterestList();
		void LoadReminderList();
		void LoadThemeList();
		void LoadUserList();

		Id GetNextDialogueId();
		Id GetNextInterestId();
		Id GetNextReminderId();
		Id GetNextThemeId();
		Id GetNextUserId();

		Dialogue** m_dialogueList{};
		Interest** m_interestList{};
		Reminder** m_reminderList{};
		Theme** m_themeList{};
		User** m_userList{};

	private:
		std::string m_dialogueListFilePath{};
		std::string m_interestListFilePath{};
		std::string m_reminderListFilePath{};
		std::string m_themeListFilePath{};
		std::string m_userListFilePath{};

		size_t m_dialogueListSize{};
		size_t m_interestListSize{};
		size_t m_reminderListSize{};
		size_t m_themeListSize{};
		size_t m_userListSize{};

		std::string m_dialogueIdCounterFilePath{};
		std::string m_interestIdCounterFilePath{};
		std::string m_reminderIdCounterFilePath{};
		std::string m_themeIdCounterFilePath{};
		std::string m_userIdCounterFilePath{};

		IdCounter m_dialogueIdCounter{};
		IdCounter m_interestIdCounter{};
		IdCounter m_reminderIdCounter{};
		IdCounter m_themeIdCounter{};
		IdCounter m_userIdCounter{};
	};
}

#endif // !STORAGE_H