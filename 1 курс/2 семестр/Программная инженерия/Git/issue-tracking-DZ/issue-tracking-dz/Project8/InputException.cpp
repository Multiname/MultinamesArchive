#include "InputException.h"

namespace BlackLine
{
	InputException::InputException(std::string message, std::string caption) : m_message(message), m_caption(caption) {}
	System::String^ InputException::GetMessage() { return gcnew System::String(m_message.c_str()); }
	System::String^ InputException::GetCaption() { return gcnew System::String(m_caption.c_str()); }
}