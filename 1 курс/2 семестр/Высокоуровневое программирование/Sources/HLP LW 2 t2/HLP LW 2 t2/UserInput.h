#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <string>
#include <iostream>
#include "InputException.h"

namespace KMK
{
	class UserInput
	{
	public:
		UserInput();

		uint16_t GetUInt16(uint16_t minimum = 0, uint16_t maximum = USHRT_MAX);
		size_t GetUInt32(size_t minimum = 0, size_t maximum = UINT_MAX);

		friend std::istream& operator>>(std::istream& in, UserInput& userInput);

	private:
		std::string m_input{};
	};
}

#endif // !USER_INPUT_H