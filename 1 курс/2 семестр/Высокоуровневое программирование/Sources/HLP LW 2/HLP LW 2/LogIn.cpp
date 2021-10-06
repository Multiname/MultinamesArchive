#include "LogIn.h"

using namespace KMK;

LogIn::LogIn(char* item_name, Func func) : ItemMenu(item_name, func) {}

char* LogIn::GetItemName()
{
	return ItemMenu::GetItemName();
}

void  LogIn::PrintItemName()
{
	ItemMenu::PrintItemName();
}

int  LogIn::run()
{
	return ItemMenu::run();
}