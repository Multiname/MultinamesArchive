#ifndef USER_H
#define USER_H
#include "AbstractItemMenu.h"

namespace KMK
{
	class User : public ItemMenu
	{
	public:
		User(char* item_name, Func func);

		char* GetItemName();
		void PrintItemName();
		int run();
	};
}

#endif // !USER_H
