#include "Vector.h"

Vector::Vector()
{
	m_list = nullptr;
	m_size = 0;
}

Vector::Vector(int* list, int size)
{
	m_list = list;
	m_size = size;
}

Vector::Vector(Vector* vector)
{
	m_list = vector->m_list;
	m_size = vector->m_size;
}

Vector::~Vector()
{
	delete m_list;
}

int Vector::GetSize()
{
	return m_size;
}

int Vector::GetElement(int position)
{
	return m_list[position];
}

int Vector::SetElement(int position, int element)
{
	if (0 <= position && position < m_size)
	{
		m_list[position] = element;
		return 0;
	}
	else
	{
		return -1;
	}
}

void Vector::AddToEnd(int element)
{
	int* temp = new int[m_size + 1];
	for (int i = 0; i < m_size; i++)
	{
		temp[i] = m_list[i];
	}
	temp[m_size] = element;

	delete[] m_list;
	m_list = temp;
	m_size++;
}

void Vector::DeleteLast()
{
	if (!CheckEmpty())
	{
		int* temp = new int[m_size - 1];
		for (int i = 0; i < m_size - 1; i++)
		{
			temp[i] = m_list[i];
		}

		delete[] m_list;
		m_list = temp;
		m_size--;
	}
}

void Vector::DeleteAll()
{
	delete[] m_list;
	m_list = nullptr;
	m_size = 0;
}

bool Vector::CheckEmpty()
{
	if (m_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}