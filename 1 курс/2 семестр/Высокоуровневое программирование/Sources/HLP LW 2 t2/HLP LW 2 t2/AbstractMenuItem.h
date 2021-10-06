#ifndef ABSTRACT_MENU_ITEM_H
#define ABSTRACT_MENU_ITEM_H
#include <string>

namespace KMK
{
	class MenuItem
	{
	public:
		MenuItem(std::string itemName);

		virtual std::string GetItemName();
		virtual void PrintItemName();
		virtual int Run() = 0;

	private:
		std::string m_itemName{};
	};
}

#endif // !ABSTRACT_MENU_ITEM_H