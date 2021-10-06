#ifndef LOG_IN_H
#define LOG_IN_H
#include "AbstractItemMenu.h"

namespace KMK
{
	class LogIn : public ItemMenu
	{
	public:
		LogIn(char* item_name, Func func);

		char* GetItemName();
		void PrintItemName();
		int run();
	};
}

#endif // !LOG_IN_H
