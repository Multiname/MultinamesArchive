#ifndef USER_STORAGE_H
#define USER_STORAGE_H
#include "User.h"
#include <vector>
#include "IdCounter.h"

namespace BlackLine
{
	class UserStorage
	{
	public:
		UserStorage();
		UserStorage(std::string path, std::string idCounter);

		void Write();
		void Read();

		void Add(User user);
		void Remove(size_t index);

		unsigned long GetNextId();
		size_t GetSize();

		User& operator[](size_t index);

	private:
		std::string m_path{};
		std::vector <User> m_userList{};
		IdCounter m_idCounter{};
	};
}

#endif // !USER_STORAGE_H