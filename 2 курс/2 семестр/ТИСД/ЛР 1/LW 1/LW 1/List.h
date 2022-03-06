#pragma once
#include <vector>
#include "ElementAccessException.h"

namespace DTAS
{
	class List
	{
	private:
		struct Element
		{
			float data{};
			Element* next{};
		};

		Element* _head{};
		Element* _currentElement{};
		int _currentPosition{};

	public:
		List();
		List(std::vector<float> data);

		std::vector<float> GetData();
		void AppendHead(float data);
		void AppendAfter(float data);
		void AppendBefore(float data);
		void Remove();
		bool FindAndSet(float data);
		bool IsEmpty();
		void Clear();

		void MoveForward();
		float GetCurrentElement();
		int GetCurrentPosition();
		void ReturnBack();
	};
}