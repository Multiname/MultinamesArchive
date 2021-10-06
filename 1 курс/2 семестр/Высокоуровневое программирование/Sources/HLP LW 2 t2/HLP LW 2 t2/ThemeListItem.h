#ifndef THEME_LIST_ITEM_H
#define THEME_LIST_ITEM_H
#include "AbstractMenuItem.h"
#include "Theme.h"
#include "Storage.h"

namespace KMK
{
	class ThemeListItem : public MenuItem
	{
	public:
		ThemeListItem(std::string itemName, Storage* storage);

		int Run();

	private:
		Storage* m_storage{};
	};
}

#endif // !THEME_LIST_ITEM_H