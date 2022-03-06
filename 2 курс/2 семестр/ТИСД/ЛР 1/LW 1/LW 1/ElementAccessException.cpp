#include "ElementAccessException.h"

namespace DTAS
{
	ElementAccessException::ElementAccessException(std::string error) : _error(error) {}
	std::string ElementAccessException::GetError() { return _error; }
}