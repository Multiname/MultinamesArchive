#pragma once
#include <vector>
#include <iostream>

namespace LITA
{
	template <typename T>
	class PriorityQueue
	{
	public:
		PriorityQueue() : _heap() {}

		void Enqueue(int priority, T data) // O(log2(n))
		{
			_heap.push_back({ priority, data }); // c1
			int size = _heap.size(); // c2
			if (size != 1) // c3
				for (int i = size / 2 - 1; i >= 0; i = (i + 1) / 2 - 1) // c4 * log2(n)
					HeapifyOnce(i); // c5 * log2(n)
		}

		T Dequeue() // O(log2(n))
		{
			T data = _heap[0].data; // c1

			int size = _heap.size(); // c2
			Swap(&_heap[0], &_heap[size - 1]); // c3

			_heap.pop_back(); // c4
			Heapify(0); // c5 * log2(n)

			return data; // c6
		}

		T Peek() { return _heap[0].data; } // O(1)

		void IncreasePriority(T data, unsigned short increase) // O(log2(n))
		{
			int size = _heap.size(); // c1
			int i; // c2
			for (i = 0; i < size; i++) // c3 * n
				if (data == _heap[i].data) // c4 * n
					break; // t1 * c5

			_heap[i].priority += increase; // c6
			for (int j = (i + 1) / 2 - 1; j >= 0; j = (j + 1) / 2 - 1) // c7 * log2(n)
				HeapifyOnce(j); // c8 * log2(n)
		}

		void PrintArray()
		{
			for (int i = 0; i < _heap.size(); ++i)
				std::cout << _heap[i].priority << ": " << _heap[i].data << "\n";
		}

	private:
		struct Pair
		{
			int priority{};
			T data{};
		};

		void Swap(Pair* a, Pair* b) // O(1)
		{
			Pair temp = *b; // c1
			*b = *a; // c2
			*a = temp; // c3
		}

		void Heapify(int i) // O(log2(n/i))
		{
			int size = _heap.size(); // c1

			int largest = i; // c2
			int l = 2 * i + 1; // c3
			int r = 2 * i + 2; // c4
			if (l < size && _heap[l].priority > _heap[largest].priority) // c5
				largest = l; // p1 * c6
			if (r < size && _heap[r].priority > _heap[largest].priority) // c7
				largest = r; // p2 * c8

			if (largest != i) // c9
			{
				Swap(&_heap[i], &_heap[largest]); // c10
				Heapify(largest); // c11 * log2(n/i)
			}
		}

		void HeapifyOnce(int i) // O(1)
		{
			int size = _heap.size(); // c1

			int largest = i; // c2
			int l = 2 * i + 1; // c3
			int r = 2 * i + 2; // c4
			if (l < size && _heap[l].priority > _heap[largest].priority) // c5
				largest = l; // p1 * c6
			if (r < size && _heap[r].priority > _heap[largest].priority) // c7
				largest = r; // p2 * c8

			Swap(&_heap[i], &_heap[largest]); // c9
		}

		std::vector<Pair> _heap{};
	};
}