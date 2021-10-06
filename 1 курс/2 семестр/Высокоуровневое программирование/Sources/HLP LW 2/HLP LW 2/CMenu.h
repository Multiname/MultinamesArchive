#ifndef CMENU_H
#define CMENU_H
#include "AbstractItemMenu.h"

namespace KMK
{
	class CMenu
	{
	public:
		CMenu(char* title, ItemMenu* items, size_t count);
		
		int GetSelect();
		bool GetRunning();
		char* GetTitle();
		size_t GetCount();
		ItemMenu* GetItems();

		void print();
		int runCommand();
		
	private:
		int m_select = -1;
		bool m_running = false;
		char* m_title = nullptr;
		size_t m_count{};
		ItemMenu* m_items = nullptr;
	};
}

#endif // !CMENU_H
