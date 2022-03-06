#include "List.h"

namespace DTAS
{
	List::List(): _head(nullptr), _currentElement(_head), _currentPosition(-1) {}

	List::List(std::vector<float> data)
	{
		if (data.size() > 0)
		{
			_head = new Element{ data[0], nullptr };
			Element* pointer = _head;
			for (unsigned short i = 1; i < data.size(); ++i)
			{
				pointer->next = new Element{ data[i], nullptr };
				pointer = pointer->next;
			}
			_currentPosition = 0;
		}
		else
		{
			_head = nullptr;
			_currentPosition = -1;
		}
		_currentElement = _head;
	}

	std::vector<float> List::GetData()
	{
		std::vector<float> data{};
		Element* pointer = _head;
		while (pointer != nullptr)
		{
			data.push_back(pointer->data);
			pointer = pointer->next;
		}
		return data;
	}

	bool List::IsEmpty()
	{
		return _head == nullptr;
	}

	void List::Clear()
	{
		while (_head != nullptr)
		{
			Element* pointer = _head;
			_head = _head->next;
			delete pointer;
		}
		_currentElement = _head;
		_currentPosition = -1;
	}

	void List::AppendHead(float data)
	{
		if (IsEmpty())
		{
			_head = new Element{ data, nullptr };
			_currentElement = _head;
			_currentPosition = 0;
		}
		else
		{
			throw ElementAccessException("List isn't empty");
		}
	}

	void List::AppendAfter(float data)
	{
		if (_currentElement == nullptr)
		{
			throw ElementAccessException("Pointer error");
		}
		else
		{
			_currentElement->next = new Element{ data, _currentElement->next };
		}
	}

	void List::AppendBefore(float data)
	{
		if (_currentElement == nullptr)
		{
			throw ElementAccessException("Pointer error");
		}
		else
		{
			if (_currentElement == _head)
			{
				_head = new Element{ data, _currentElement };
			}
			else
			{
				Element* pointer = _head;
				while (pointer->next != _currentElement)
				{
					pointer = pointer->next;
				}
				pointer->next = new Element{ data, _currentElement };
			}
			++_currentPosition;
		}
	}

	void List::Remove()
	{
		if (_currentElement == nullptr)
		{
			throw ElementAccessException("Pointer error");
		}
		else
		{
			if (_currentElement == _head)
			{
				_head = _head->next;
				delete _currentElement;
				_currentElement = _head;
			}
			else
			{
				Element* pointer = _head;
				while (pointer->next != _currentElement)
				{
					pointer = pointer->next;
				}
				_currentElement = _currentElement->next;
				delete pointer->next;
				pointer->next = _currentElement;
			}
			if (_currentElement == nullptr)
			{
				_currentPosition = -1;
			}
		}
	}

	bool List::FindAndSet(float data)
	{
		Element* pointer = _currentElement;
		int newPosition = _currentPosition;
		if (pointer != nullptr)
		{
			pointer = pointer->next;
			++newPosition;
		}
		while (pointer != nullptr)
		{
			if (pointer->data == data)
			{
				_currentElement = pointer;
				_currentPosition = newPosition;
				return true;
			}
			else
			{
				pointer = pointer->next;
				++newPosition;
			}
		}
		pointer = _head;
		newPosition = 0;
		while (pointer != _currentElement)
		{
			if (pointer->data == data)
			{
				_currentElement = pointer;
				_currentPosition = newPosition;
				return true;
			}
			else
			{
				pointer = pointer->next;
				++newPosition;
			}
		}
		if (_currentElement != nullptr && _currentElement->data == data)
		{
			return true;
		}
		return false;
	}

	void List::MoveForward()
	{
		if (_currentElement != nullptr)
		{
			_currentElement = _currentElement->next;
			if (_currentElement != nullptr)
			{
				++_currentPosition;
			}
			else
			{
				_currentPosition = -1;
			}
		}
	}

	float List::GetCurrentElement()
	{
		if (_currentElement != nullptr)
		{
			return _currentElement->data;
		}
		else
		{
			throw ElementAccessException("Pointer error");
		}
	}

	int List::GetCurrentPosition()
	{
		return _currentPosition;
	}

	void List::ReturnBack()
	{
		_currentElement = _head;
		if (_currentElement != nullptr)
		{
			_currentPosition = 0;
		}
		else
		{
			_currentPosition = -1;
		}
	}
}