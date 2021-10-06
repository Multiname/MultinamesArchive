#ifndef ABSTRACT_ITEM_MENU_H
#define ABSTRACT_ITEM_MENU_H

namespace KMK
{
	extern const int LENGTH_OF_FIELD;
	typedef int (*Func)();

	class ItemMenu
	{
	public:
		ItemMenu(char* item_name, Func func);

		virtual char* GetItemName();
		virtual void PrintItemName();
		virtual int run();

	protected:
		char* m_item_name = nullptr;
		Func m_func = nullptr;
	};
}

#endif // !ABSTRACT_ITEM_MENU_H
