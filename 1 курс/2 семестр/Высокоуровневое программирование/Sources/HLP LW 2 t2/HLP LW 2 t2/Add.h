#ifndef ADD_H
#define ADD_H
#include "Entity.h"

namespace KMK
{
	template<typename T>
	void Add(T**& entities, size_t& size, T* newElement)
	{
		T** temp = new T * [size + 1]{};

		for (Iteration i{}; i < size; ++i)
		{
			temp[i] = entities[i];
		}

		temp[size] = newElement;

		delete[] entities;
		entities = temp;
		++size;
	}
}

#endif // !ADD_H