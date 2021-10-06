#include "RoomStorage.h"
#include <fstream>

namespace BlackLine
{
	RoomStorage::RoomStorage() : m_idCounter()
	{
		m_path = {};
		m_roomList = {};
	}

	RoomStorage::RoomStorage(std::string path, std::string idCounter) : m_idCounter(idCounter)
	{
		m_path = path;
		Read();
	}

	void RoomStorage::Write()
	{
		std::ofstream fileWrite(m_path, std::ios::binary);

		size_t size = m_roomList.size();
		fileWrite.write((char*)&size, sizeof(size_t));

		std::vector <Room>::const_iterator it = m_roomList.begin();
		while (it != m_roomList.end())
		{
			fileWrite.write((char*)&it->id, sizeof(unsigned long));
			fileWrite.write((char*)&it->number, sizeof(unsigned short));
			fileWrite.write((char*)&it->cost, sizeof(unsigned long));

			fileWrite.write((char*)&it->description.wifi, sizeof(bool));
			fileWrite.write((char*)&it->description.television, sizeof(bool));

			size_t stringSize = it->description.sleepingPlace.length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(it->description.sleepingPlace.c_str(), stringSize);

			stringSize = it->description.roomSize.length() + 1;
			fileWrite.write((char*)&stringSize, sizeof(size_t));
			fileWrite.write(it->description.roomSize.c_str(), stringSize);

			fileWrite.write((char*)&it->isAvailable, sizeof(bool));

			++it;
		}

		fileWrite.close();
	}

	void RoomStorage::Read()
	{
		std::ifstream fileRead(m_path, std::ios::binary);

		size_t size{};
		fileRead.read((char*)&size, sizeof(size_t));

		for (size_t i{}; i < size; ++i)
		{
			Room room{};
			fileRead.read((char*)&room.id, sizeof(unsigned long));
			fileRead.read((char*)&room.number, sizeof(unsigned short));
			fileRead.read((char*)&room.cost, sizeof(unsigned long));

			fileRead.read((char*)&room.description.wifi, sizeof(bool));
			fileRead.read((char*)&room.description.television, sizeof(bool));

			size_t stringSize{};
			fileRead.read((char*)&stringSize, sizeof(size_t));
			char* str = new char[stringSize]{};
			fileRead.read(str, stringSize);
			room.description.sleepingPlace = str;
			delete[] str;

			fileRead.read((char*)&stringSize, sizeof(size_t));
			str = new char[stringSize] {};
			fileRead.read(str, stringSize);
			room.description.roomSize = str;
			delete[] str;

			fileRead.read((char*)&room.isAvailable, sizeof(bool));

			m_roomList.push_back(room);
		}

		fileRead.close();
	}

	void RoomStorage::Add(Room room)
	{
		m_roomList.push_back(room);
		Sort();
		Write();
	}

	void RoomStorage::Remove(size_t index)
	{
		m_roomList.erase(m_roomList.begin() + index);
		Write();
	}

	void RoomStorage::Sort()
	{
		for (size_t i = m_roomList.size(); i > 0; --i)
		{
			for (size_t j{}; j < i - 1; ++j)
			{
				if (m_roomList[j].number > m_roomList[j + 1].number)
				{
					Room temp = m_roomList[j];
					m_roomList[j] = m_roomList[j + 1];
					m_roomList[j + 1] = temp;
				}
			}
		}
	}

	unsigned long RoomStorage::GetNextId() { return m_idCounter(); }
	size_t RoomStorage::GetSize() { return m_roomList.size(); }

	Room& RoomStorage::operator[](size_t index) { return m_roomList[index]; }
}