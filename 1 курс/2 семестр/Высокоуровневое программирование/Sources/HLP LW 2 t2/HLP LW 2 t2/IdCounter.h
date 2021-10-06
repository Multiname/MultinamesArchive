#ifndef ID_COUNTER_H
#define ID_COUNTER_H
#include "TypeDefinitions.h"
#include <string>

namespace KMK
{
	class IdCounter
	{
	public:
		IdCounter();
		IdCounter(std::string storageFile);

		void SetIdCounter(std::string storageFile);

		Id operator() ();

	private:
		Id m_id{};
		std::string m_storageFile{};
	};
}

#endif // !ID_COUNTER_H