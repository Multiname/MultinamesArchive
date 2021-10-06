#ifndef DIALOGUE_LIST_ITEM_H
#define DIALOGUE_LIST_ITEM_H
#include "AbstractMenuItem.h"
#include "Dialogue.h"
#include "Storage.h"

namespace KMK
{
	class DialogueListItem : public MenuItem
	{
	public:
		DialogueListItem(std::string itemName, Storage* storage);

		int Run();

	private:
		Storage* m_storage{};
	};
}

#endif // !DIALOGUE_LIST_ITEM_H