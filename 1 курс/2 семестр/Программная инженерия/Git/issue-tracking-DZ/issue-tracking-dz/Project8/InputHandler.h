#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include "InputException.h"

namespace BlackLine
{
	class InputHandler
	{
	public:
		InputHandler();
		InputHandler(System::String^ input);

		unsigned short GetDay();
		unsigned short GetMonth();
		unsigned short GetYear();
		std::string GetLogin();
		std::string GetPassword();
		std::string GetNickname();
		unsigned long GetCost();
		std::string GetSquare();

	private:
		std::string m_content{};
	};
}

#endif // !INPUT_HANDLER_H