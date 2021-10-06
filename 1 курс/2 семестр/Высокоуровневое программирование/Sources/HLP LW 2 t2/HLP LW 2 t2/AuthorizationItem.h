#ifndef AUTHORIZATION_ITEM_H
#define AUTHORIZATION_ITEM_H
#include "AbstractMenuItem.h"
#include "Storage.h"

namespace KMK
{
	class AuthorizstionItem : public MenuItem
	{
	public:
		AuthorizstionItem(std::string itemName, Storage* storage);

		int Run();

	private:
		Storage* m_storage{};
	};
}

#endif // !AUTHORIZATION_ITEM_H