#include "NewUser.h"

using namespace KMK;

NewUser::NewUser(char* item_name, Func func) : ItemMenu(item_name, func) {}

char* NewUser::GetItemName()
{
	return ItemMenu::GetItemName();
}

void  NewUser::PrintItemName()
{
	ItemMenu::PrintItemName();
}

int  NewUser::run()
{
	return ItemMenu::run();
}