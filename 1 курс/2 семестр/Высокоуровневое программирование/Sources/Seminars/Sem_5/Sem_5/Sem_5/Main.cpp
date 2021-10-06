/*
	Создать свой вектор
	Операции вектора:
		Конструктор (без параметров, с параметрами)
		Деструктор
		Очистка от всех элементов
		Перегрузка оператора доступа к элементу
		Метод изменения размера с сохранением существующих элементов (если новый размер больше)
		Вставка элемента по индексу
		Удаление по индексу
		Вставка в начало
		Вставка в конец
		Получение длины
	Класс должен быть шаблонным

	Операции итератора:
		Перегрузки +, -, ++, --, !=, ==, *
		Методы begin, end
*/

#include <iostream>

using namespace std;

template<typename T>
class MyVector
{
public:
	MyVector()
	{
		m_array = nullptr;
		m_size = 0;
	}

	MyVector(size_t size)
	{
		m_array = new T[size]{};
		m_size = size;
	}

	~MyVector()
	{
		delete[] m_array;
	}

	void Clear()
	{
		delete[] m_array;
		m_array = nullptr;
		m_size = 0;
	}

	T& operator[](int index)
	{
		return m_array[index];
	}

	void ChangeSize(int newSize)
	{
		if (newSize != m_size)
		{
			T* temp = new T[newSize]{};

			if (newSize > m_size)
			{
				for (size_t i{}; i < m_size; ++i)
				{
					temp[i] = m_array[i];
				}
			}
			else if (newSize < m_size)
			{
				for (size_t i{}; i < newSize; ++i)
				{
					temp[i] = m_array[i];
				}
			}

			Clear();
			m_array = temp;
			m_size = newSize;
		}
	}

	void Insert(size_t index, T element)
	{
		ChangeSize(m_size + 1);
		for (size_t i = m_size - 1; i > index ; --i)
		{
			m_array[i] = m_array[i - 1];
		}
		m_array[index] = element;
	}

	void InsertToBeginning(T element)
	{
		Insert(0, element);
	}

	void InsertToEnding(T element)
	{
		Insert(m_size - 1, element);
	}

	void Remove(size_t index)
	{
		for (size_t i = index; i < m_size - 1; ++i)
		{
			m_array[i] = m_array[i + 1];
		}
		ChangeSize(m_size - 1);
	}

	size_t GetSize()
	{
		return m_size;
	}

	class Iterator
	{
	public:
		Iterator()
		{
			m_pointer = nullptr;
		}

		Iterator(T* element)
		{
			m_pointer = element;
		}

		Iterator(Iterator& iterator)
		{
			m_pointer = iterator.m_pointer;
		}

		Iterator& operator++()
		{
			++m_pointer;
			return *this;
		}

		Iterator& operator++(int)
		{
			Iterator temp(m_pointer);
			++this;
			return temp;
		}

		Iterator& operator--()
		{
			--m_pointer;
			return m_pointer;
		}

		Iterator& operator--(int)
		{
			Iterator temp(m_pointer);
			--this;
			return temp;
		}

		T* operator*()
		{
			return *m_pointer;
		}

		bool operator==(Iterator iterator)
		{
			return m_pointer == iterator.m_pointer;
		}

		bool operator!=(Iterator iterator)
		{
			return m_pointer != iterator.m_pointer;
		}

		friend Iterator& operator+(Iterator iterator, int number)
		{
			m_pointer += number;
			return m_pointer;
		}

		friend Iterator& operator-(Iterator iterator, int number)
		{
			m_pointer -= number;
			return m_pointer;
		}

	private:
		T* m_pointer{};
	};

	Iterator& begin()
	{
		Iterator iterator(m_array);
		return iterator;
	}

	Iterator& end()
	{
		Iterator iterator(m_array + m_size);
		return iterator;
	}

private:
	T* m_array{};
	size_t m_size{};
};

int main()
{
	//MyVector<int> arr{5};
	//arr[0] = 10;
	//cout << arr[0] << endl << endl;
	//
	//arr.Insert(0, 15);
	//cout << arr[0] << endl;
	//cout << arr[1] << endl;
	//cout << arr[5] << endl << endl;

	//arr.Remove(0);
	//cout << arr[0] << endl;
	//cout << arr.GetSize() << endl << endl;

	MyVector<int> arr{ 5 };
	arr[0] = 1;
	MyVector<int>::Iterator iterator{ arr.begin() };

	int i = 1;

	cout << *iterator << endl;

	//cout << *arr.begin() << " " << *iterator << " " << *arr.end() << endl;

	for (iterator = arr.begin(); iterator != arr.end(); ++iterator)
	{
		*iterator = i;
		++i;
	}

	for (iterator = arr.begin(); iterator != arr.end(); ++iterator)
	{
		cout << *iterator << "\n";
	}

	return 0;
}