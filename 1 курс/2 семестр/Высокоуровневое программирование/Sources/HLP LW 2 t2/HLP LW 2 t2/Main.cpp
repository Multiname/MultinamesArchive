#include "Menu.h"
#include "UserListItem.h"
#include "DialogueListItem.h"
#include "InterestListItem.h"
#include "ReminderListItem.h"
#include "ThemeListItem.h"
#include <iostream>
#include "Storage.h"
#include "AuthorizationItem.h"

using namespace KMK;

int main()
{
	Storage* storage = new Storage("Dialogue database.dat", "Interst database.dat",
		"Reminder database.dat", "Theme database.dat", "User database.dat", "Dialogue IDs.dat", "Interst IDs.dat",
		"Reminder IDs.dat", "Theme and user IDs.dat", "Theme and user IDs.dat");

	UserListItem users = UserListItem("User list", storage);
	DialogueListItem dialogs = DialogueListItem("Dialogue list", storage);
	InterestListItem interests = InterestListItem("Interest list", storage);
	ReminderListItem reminders = ReminderListItem("Reminder list", storage);
	ThemeListItem themes = ThemeListItem("Theme list", storage);

	AuthorizstionItem authorization = AuthorizstionItem("Log in / sign in", storage);

	Menu menu = Menu("Waffle Chat", new MenuItem*[6] { &users, &dialogs, &interests, &reminders, &themes, &authorization }, 6);

	std::cin >> menu;

	return 0;
}