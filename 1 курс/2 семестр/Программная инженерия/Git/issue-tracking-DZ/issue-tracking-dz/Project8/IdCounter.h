#ifndef ID_COUNTER_H
#define ID_COUNTER_H
#include <string>

namespace BlackLine
{
	class IdCounter
	{
	public:
		IdCounter();
		IdCounter(std::string storageFile);

		unsigned long operator() ();

	private:
		unsigned long m_id{};
		std::string m_storageFile{};
	};
}

#endif // !ID_COUNTER_H