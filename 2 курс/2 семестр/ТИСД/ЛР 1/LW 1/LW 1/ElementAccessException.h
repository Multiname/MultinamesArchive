#pragma once
#include <string>

namespace DTAS
{
	class ElementAccessException
	{
	public:
		ElementAccessException(std::string error);
		std::string GetError();

	private:
		std::string _error{};
	};
}