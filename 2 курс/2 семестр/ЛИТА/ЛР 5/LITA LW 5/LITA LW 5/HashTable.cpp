#include "HashTable.h"
#include <iostream>

namespace LITA_LW_5
{
	HashTable::HashTable(size_t size) : _size(size), _elementsNumber(0),
		_table(new Record* [size] {}) {}
	HashTable::~HashTable()
	{
		for (size_t i{}; i < _size; ++i)
			delete _table[i];
		delete[] _table;
	}

	void HashTable::Add(int key, std::string data)
	{
		size_t i = 0;
		size_t hash{};
		do
		{
			hash = (key + i++) % _size;
		} while (_table[hash] != nullptr);
		_table[hash] = new Record{ key, data };
		++_elementsNumber;
		if (GetOccupancyRate() > _MaxLoadFactor)
			Expand();
	}

	bool HashTable::Find(int key, std::string& data)
	{
		size_t i = 0;
		size_t hash = (key + i++) % _size;
		while (_table[hash] != nullptr)
		{
			if (_table[hash]->key == key)
			{
				data = _table[hash]->data;
				return true;
			}
			hash = (key + i++) % _size;
		}

		return false;
	}

	void HashTable::Print()
	{
		for (size_t i{}; i < _size; ++i)
			if (_table[i] != nullptr)
				std::cout << i << " " << _table[i]->key << " "
				<< _table[i]->data << "\n";
			else
				std::cout << i << "\n";
		std::cout << "\n";
	}

	float HashTable::GetOccupancyRate() { return (float)_elementsNumber / _size; }

	void HashTable::Expand()
	{
		Record** expanded = new Record * [_size * _ExpandFactor]{};
		for (size_t i{}; i < _size; ++i)
		{
			if (_table[i] != nullptr)
			{
				size_t j = 0;
				size_t hash{};
				do
				{
					hash = (_table[i]->key + j++) % (_size * _ExpandFactor);
				} while (expanded[hash] != nullptr);
				expanded[hash] = new Record{ _table[i]->key, _table[i]->data };

				delete _table[i];
			}
		}

		delete[] _table;
		_table = expanded;
		_size *= _ExpandFactor;
	}
}