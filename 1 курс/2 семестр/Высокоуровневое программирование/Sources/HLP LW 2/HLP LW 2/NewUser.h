#ifndef NEW_USER_H
#define NEW_USER_H
#include "AbstractItemMenu.h"

namespace KMK
{
	class NewUser : public ItemMenu
	{
	public:
		NewUser(char* item_name, Func func);

		char* GetItemName();
		void PrintItemName();
		int run();
	};
}

#endif // !NEW_USER_H
