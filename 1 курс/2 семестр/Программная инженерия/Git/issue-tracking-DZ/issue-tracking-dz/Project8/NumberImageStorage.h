#ifndef NUMBER_IMAGE_STORAGE_H
#define NUMBER_IMAGE_STORAGE_H
#include <vector>
#include <string>

namespace BlackLine
{
	class NumberImageStorage
	{
	public:
		NumberImageStorage();
		NumberImageStorage(std::string storagePath);

		System::String^ GetPathById(unsigned long id);

		void Add(unsigned long id, System::String^ sourcePath);
		void Remove(unsigned long id);

		void Save();
		void Load();

	private:
		std::vector<unsigned long> m_numberIDs{};
		std::string m_storagePath;
	};
}

#endif // !NUMBER_IMAGE_STORAGE_H