#include "InputException.h"

namespace KMK
{
	InputException::InputException(const char* error) { m_error = error; }

	const char* InputException::GetError() { return m_error; }

	StringToUInt16Exception::StringToUInt16Exception(const char* error) : InputException(error) {}

	StringToUInt32Exception::StringToUInt32Exception(const char* error) : InputException(error) {}
}