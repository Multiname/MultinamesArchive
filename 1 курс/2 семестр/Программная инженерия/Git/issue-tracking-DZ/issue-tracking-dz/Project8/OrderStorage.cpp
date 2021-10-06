#include "OrderStorage.h"
#include <fstream>

namespace BlackLine
{
	OrderStorage::OrderStorage() : m_idCounter()
	{
		m_path = {};
		m_orderList = {};
	}

	OrderStorage::OrderStorage(std::string path, std::string idCounter) : m_idCounter(idCounter)
	{
		m_path = path;
		Read();
	}

	void OrderStorage::Write()
	{
		std::ofstream fileWrite(m_path, std::ios::binary);

		size_t size = m_orderList.size();
		fileWrite.write((char*)&size, sizeof(size_t));
		
		std::vector <Order>::const_iterator it = m_orderList.begin();
		while (it != m_orderList.end())
		{
			fileWrite.write((char*)&*it, sizeof(Order));
			++it;
		}

		fileWrite.close();
	}

	void OrderStorage::Read()
	{
		std::ifstream fileRead(m_path, std::ios::binary);

		size_t size{};
		fileRead.read((char*)&size, sizeof(size_t));

		for (size_t i{}; i < size; ++i)
		{
			Order order{};
			fileRead.read((char*)&order, sizeof(Order));
			m_orderList.push_back(order);
		}

		fileRead.close();
	}

	void OrderStorage::Add(Order order)
	{
		m_orderList.push_back(order);
		Sort();
		Write();
	}

	void OrderStorage::Remove(size_t index)
	{
		m_orderList.erase(m_orderList.begin() + index);
		Write();
	}

	void OrderStorage::Sort()
	{
		for (size_t i = m_orderList.size(); i > 0; --i)
		{
			for (size_t j{}; j < i - 1; ++j)
			{
				if (m_orderList[j].startDate.day +
					m_orderList[j].startDate.month * 100 +
					m_orderList[j].startDate.year * 10000 >
					m_orderList[j + 1].startDate.day +
					m_orderList[j + 1].startDate.month * 100 +
					m_orderList[j + 1].startDate.year * 10000)
				{
					Order temp = m_orderList[j];
					m_orderList[j] = m_orderList[j + 1];
					m_orderList[j + 1] = temp;
				}
			}
		}
	}

	unsigned long OrderStorage::GetNextId() { return m_idCounter(); }
	size_t OrderStorage::GetSize() { return m_orderList.size(); }

	Order& OrderStorage::operator[](size_t index) { return m_orderList[index]; }
}