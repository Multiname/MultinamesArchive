#ifndef ORDER_STORAGE_H
#define ORDER_STORAGE_H
#include "Order.h"
#include <vector>
#include "IdCounter.h"

namespace BlackLine
{
	class OrderStorage
	{
	public:
		OrderStorage();
		OrderStorage(std::string path, std::string idCounter);

		void Write();
		void Read();

		void Add(Order order);
		void Remove(size_t index);
		void Sort();

		unsigned long GetNextId();
		size_t GetSize();

		Order& operator[](size_t index);

	private:
		std::string m_path{};
		std::vector <Order> m_orderList{};
		IdCounter m_idCounter{};
	};
}

#endif // !ORDER_STORAGE_H