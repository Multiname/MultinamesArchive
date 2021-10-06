#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H
#include <string>

namespace BlackLine
{
	class InputException
	{
	public:
		InputException(std::string message, std::string caption);

		System::String^ GetMessage();
		System::String^ GetCaption();

	private:
		std::string m_message{};
		std::string m_caption{};
	};
}

#endif // !INPUT_EXCEPTION_H