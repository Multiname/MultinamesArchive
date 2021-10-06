#ifndef ROOM_STORAGE_H
#define ROOM_STORAGE_H
#include "Room.h"
#include <vector>
#include "IdCounter.h"

namespace BlackLine
{
	class RoomStorage
	{
	public:
		RoomStorage();
		RoomStorage(std::string path, std::string idCounter);

		void Write();
		void Read();

		void Add(Room room);
		void Remove(size_t index);
		void Sort();

		unsigned long GetNextId();
		size_t GetSize();

		Room& operator[](size_t index);

	private:
		std::string m_path{};
		std::vector <Room> m_roomList{};
		IdCounter m_idCounter{};
	};
}

#endif // !ROOM_STORAGE_H