#ifndef INTEREST_LIST_ITEM_H
#define INTEREST_LIST_ITEM_H
#include "AbstractMenuItem.h"
#include "Interest.h"
#include "Storage.h"

namespace KMK
{
	class InterestListItem : public MenuItem
	{
	public:
		InterestListItem(std::string itemName, Storage* storage);

		int Run();

	private:
		Storage* m_storage{};
	};
}

#endif // !INTEREST_LIST_ITEM_H