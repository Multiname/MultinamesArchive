#ifndef MENU_H
#define MENU_H
#include "AbstractMenuItem.h"
#include <iostream>

namespace KMK
{
	class Menu
	{
	public:
		Menu(std::string title, MenuItem** items, size_t count);

		int GetSelect();
		bool GetRunning();
		std::string GetTitle();
		size_t GetCount();
		MenuItem** GetItems();

		void Print() const;
		int RunCommand() const;

		friend std::ostream& operator<<(std::ostream& out, const Menu& menu);
		friend std::istream& operator>>(std::istream& in, const Menu& menu);

	private:
		int m_select = -1;
		bool m_running = false;
		std::string m_title{};
		size_t m_count{};
		MenuItem** m_items = nullptr;
	};

	std::ostream& operator<<(std::ostream& out, const Menu& menu);
	std::istream& operator>>(std::istream& in, const Menu& menu);
}

#endif // !MENU_H