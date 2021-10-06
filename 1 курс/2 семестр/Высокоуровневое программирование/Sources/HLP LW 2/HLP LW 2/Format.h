#ifndef FORMAT_H
#define FORMAT_H
#include "AbstractItemMenu.h"

namespace KMK
{
	class Format : public ItemMenu
	{
	public:
		Format(char* item_name, Func func);

		char* GetItemName();
		void PrintItemName();
		int run();
	};
}

#endif // !FORMAT_H
