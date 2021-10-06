#include "Format.h"

using namespace KMK;

Format::Format(char* item_name, Func func) : ItemMenu(item_name, func) {}

char* Format::GetItemName()
{
	return ItemMenu::GetItemName();
}

void  Format::PrintItemName()
{
	ItemMenu::PrintItemName();
}

int  Format::run()
{
	return ItemMenu::run();
}