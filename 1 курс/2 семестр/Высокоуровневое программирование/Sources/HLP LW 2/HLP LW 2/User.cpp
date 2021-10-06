#include "User.h"

using namespace KMK;

User::User(char* item_name, Func func) : ItemMenu(item_name, func) {}

char* User::GetItemName()
{
	return ItemMenu::GetItemName();
}

void  User::PrintItemName()
{
	ItemMenu::PrintItemName();
}

int  User::run()
{
	return ItemMenu::run();
}