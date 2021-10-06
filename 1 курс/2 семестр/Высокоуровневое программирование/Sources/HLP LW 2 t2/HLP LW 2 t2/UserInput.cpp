#include "UserInput.h"

namespace KMK
{
	UserInput::UserInput() { m_input = {}; }

	uint16_t UserInput::GetUInt16(uint16_t minimum, uint16_t maximum)
	{
		if (m_input.size() == 0)
		{
			throw StringToUInt16Exception("Error: the input is empty");
		}
		if (m_input.size() > 5)
		{
			throw StringToUInt16Exception("Error: too many symbols");
		}

		for (size_t i{}; i < m_input.size(); ++i)
		{
			if (!isdigit(m_input[i]))
			{
				throw StringToUInt16Exception("Error: there are not only digits in the input");
			}
		}

		uint32_t UInt32Input = std::stoul(m_input);

		if (UInt32Input < minimum || UInt32Input > maximum)
		{
			throw StringToUInt16Exception("Error: the number is out of range");
		}
		else
		{
			return (uint16_t)UInt32Input;
		}
	}

	size_t UserInput::GetUInt32(size_t minimum, size_t maximum)
	{
		if (m_input.size() == 0)
		{
			throw StringToUInt32Exception("Error: the input is empty");
		}
		if (m_input.size() > 10)
		{
			throw StringToUInt32Exception("Error: too many symbols");
		}

		for (size_t i{}; i < m_input.size(); ++i)
		{
			if (!isdigit(m_input[i]))
			{
				throw StringToUInt32Exception("Error: there are not only digits in the input");
			}
		}

		uint32_t UInt32Input{};
		try
		{
			UInt32Input = std::stoul(m_input);
		}
		catch (std::out_of_range)
		{
			throw StringToUInt32Exception("Error: the number is too big");
		}

		if (UInt32Input < minimum || UInt32Input > maximum)
		{
			throw StringToUInt32Exception("Error: the number is out of range");
		}
		else
		{
			return UInt32Input;
		}
	}

	std::istream& operator>>(std::istream& in, UserInput& userInput)
	{
		std::getline(in, userInput.m_input);
		return in;
	}
}