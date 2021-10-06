#ifndef LOG_IN_ITEM_H
#define LOG_IN_ITEM_H
#include "AbstractMenuItem.h"

namespace KMK
{
	class LogInItem : public MenuItem
	{
	public:
		LogInItem(char* itemName, char* tempDataBase, char* dataBase);

		int Run();

	private:
		char* m_tempDataBase = nullptr;
		char* m_dataBase = nullptr;
	};
}

#endif // !LOG_IN_ITEM_H