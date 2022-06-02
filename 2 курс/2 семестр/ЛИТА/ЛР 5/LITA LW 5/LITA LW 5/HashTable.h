#pragma once
#include <string>
namespace LITA_LW_5
{
	class HashTable
	{
	public:
		HashTable(size_t size);
		~HashTable();

		void Add(int key, std::string data);
		bool Find(int key, std::string& data);

		void Print();
	private:
		float GetOccupancyRate();
		void Expand();

		struct Record
		{
			int key{};
			std::string data{};
		};

		size_t _size{};
		Record** _table = nullptr;
		size_t _elementsNumber = 0;

		float _MaxLoadFactor = 0.7;
		uint16_t _ExpandFactor = 2;
	};
}