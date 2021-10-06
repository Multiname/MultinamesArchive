#include "InputHandler.h"
#include <msclr\marshal_cppstd.h>
#include <ios>

namespace BlackLine
{
	InputHandler::InputHandler() { m_content = {}; }
	InputHandler::InputHandler(System::String^ input) { m_content = msclr::interop::marshal_as<std::string>(input); }

	unsigned short InputHandler::GetDay()
	{
		if (m_content.size() == 0) { throw
			InputException("Строка для ввода пуста, введите день (1-2 цифры)", "Пустая строка"); }
		if (m_content.size() > 2) { throw
			InputException("Количество символов больше 2, попробуйте ввести день еще раз (1-2 цифры)",
			"Слишком много символов"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("В введенной строке присутствуют символы, не являющиеся цифрами, попробуйте ввести день еще раз (1-2 цифры)",
					"Введены не цифровые символы"); }
			if (!isdigit(m_content[i])) { throw
				InputException("В введенной строке присутствуют символы, не являющиеся цифрами, попробуйте ввести день еще раз (1-2 цифры)",
				"Введены не цифровые символы"); }
		}

		unsigned short day = std::stoi(m_content);
		if (day > 31) { throw InputException("День введен неправильно, число не может быть больше 31",
			"Слишком большое число"); }
		if (day == 0) { throw InputException("День введен неправильно, число не может равняться 0",
			"Слишком маленькое число"); }

		return day;
	}

	unsigned short InputHandler::GetMonth()
	{
		if (m_content.size() == 0) { throw InputException("Строка для ввода пуста, введите месяц (1-2 цифры)",
			"Пустая строка"); }
		if (m_content.size() > 2) { throw
			InputException("Количество символов больше 2, попробуйте ввести месяц еще раз (1-2 цифры)",
			"Слишком много символов"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("В введенной строке присутствуют символы, не являющиеся цифрами, попробуйте ввести месяц еще раз (1-2 цифры)",
					"Введены не цифровые символы");	}
			if (!isdigit(m_content[i])) { throw
				InputException("В введенной строке присутствуют символы, не являющиеся цифрами, попробуйте ввести месяц еще раз (1-2 цифры)",
						"Введены не цифровые символы"); }
		}

		unsigned short month = std::stoi(m_content);
		if (month > 12) { throw InputException("Месяц введен неправильно, число не может быть больше 12",
			"Слишком большое число"); }
		if (month == 0) { throw InputException("Месяц введен неправильно, число не может равняться 0",
			"Слишком маленькое число"); }

		return month;
	}

	unsigned short InputHandler::GetYear()
	{
		if (m_content.size() == 0) { throw InputException("Строка для ввода пуста, введите год (4 цифры)",
			"Пустая строка"); }
		if (m_content.size() != 4) { throw InputException("Количество символов не равно 4, попробуйте ввести год еще раз ",
			"Неверное число символов"); }
		if (m_content[0] < 0 || m_content[0] > 255 || m_content[1] < 0 || m_content[1] > 255 ||
			m_content[2] < 0 || m_content[2] > 255 || m_content[3] < 0 || m_content[3] > 255) { throw
			InputException("В введенной строке присутствуют символы, не являющиеся цифрами, попробуйте ввести год еще раз (4 цифры)",
				"Введены не цифровые символы"); }
		if (!isdigit(m_content[0]) || !isdigit(m_content[1]) || !isdigit(m_content[2]) || !isdigit(m_content[3]))
		{ throw InputException("В введенной строке присутствуют символы, не являющиеся цифрами, попробуйте ввести год еще раз (4 цифры)", 
			"Введены не цифровые символы"); }

		return std::stoi(m_content);
	}

	std::string InputHandler::GetLogin()
	{
		if (m_content.size() < 5) { throw InputException("Слишком мало символов, введите логин еще раз (5-20 символов)",
				"Слишком мало символов"); }
		if (m_content.size() > 20) { throw InputException("Слишком много символов, введите логин еще раз (5-20 символов)",
				"Слишком много символов"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("В логине присутствуют неверные символы, используйте только английские буквы и цифры",
					"Неверные символы"); }
			if (!isalpha(m_content[i]) && !isdigit(m_content[i])) { throw
				InputException("В логине присутствуют неверные символы, используйте только английские буквы и цифры",
					"Неверные символы"); }
		}

		return m_content;
	}

	std::string InputHandler::GetPassword()
	{
		if (m_content.size() < 5) { throw InputException("Слишком мало символов, введите пароль еще раз (5-20 символов)",
				"Слишком мало символов"); }
		if (m_content.size() > 20) { throw InputException("Слишком много символов, введите пароль еще раз (5-20 символов)",
				"Слишком много символов"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("В пароле присутствуют неверные символы, используйте только английские буквы и цифры",
					"Неверные символы"); }
			if (!isalpha(m_content[i]) && !isdigit(m_content[i])) { throw
				InputException("В пароле присутствуют неверные символы, используйте только английские буквы и цифры",
					"Неверные символы"); }
		}

		return m_content;
	}

	std::string InputHandler::GetNickname()
	{
		if (m_content.size() < 5) { throw InputException("Слишком мало символов, введите имя еще раз (5-40 символов)",
				"Слишком мало символов"); }
		if (m_content.size() > 40) { throw InputException("Слишком много символов, введите имя еще раз (5-40 символов)",
				"Слишком много символов"); }
		if (m_content[0] == ' ' || m_content[m_content.size() - 1] == ' ') { throw
			InputException("В конце или начале имени стоит пробел, он может находиться только внутри",
					"Пробел в конце или начале"); }
		if (m_content[0] == '.') { throw
			InputException("В начале имени стоит точка, она может находиться только внутри или на конце",
					"Точка в начале"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("В имени выбран неправильный язык, используйте английский язык",
					"Неверный язык"); }
			if (!isalpha(m_content[i]) && m_content[i] != ' ' && m_content[i] != '.') { throw 
				InputException("В имени введены неправильные символы, используйте только английские буквы, точки и пробелы",
					"Неверные символы"); }
			if (m_content[i] == ' ' && m_content[i + 1] == ' ') { throw
				InputException("В имени встречаются 2 пробела подряд, попробуйте еще раз",
					"Двойной пробел"); }
			if (m_content[i] == '.' && m_content[i + 1] == '.') { throw
				InputException("В имени встречаются 2 точки подряд, попробуйте еще раз",
					"Две точки подряд"); }
		}

		return m_content;
	}

	unsigned long InputHandler::GetCost()
	{
		if (m_content.size() == 0) { throw InputException("Строка для ввода пуста, введите цену",
			"Пустая строка"); }
		if (m_content.size() > 10) { throw
			InputException("Слишком много символов, введите цену еще раз",
				"Слишком много символов"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("Использованы неверные символы, цена может содержать только цифры",
					"Неверные символы"); }
			if (!isdigit(m_content[i])) { throw
				InputException("Использованы неверные символы, цена может содержать только цифры",
					"Неверные символы"); }
		}

		unsigned long cost{};
		try
		{
			cost = std::stoul(m_content);
		}
		catch (std::out_of_range)
		{
			throw InputException("Слишком большое число, введите цену еще раз",
				"Слишком большое число");
		}

		return cost;
	}

	std::string InputHandler::GetSquare()
	{
		if (m_content.size() == 0) { throw InputException("Строка для ввода пуста, введите площадь",
			"Пустая строка"); }
		if (m_content.size() > 3) { throw
			InputException("Слишком много символов, введите площадь еще раз",
				"Слишком много символов"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("Использованы неверные символы, площадь может содержать только цифры",
					"Неверные символы"); }
			if (!isdigit(m_content[i])) { throw
				InputException("Использованы неверные символы, площадь может содержать только цифры",
					"Неверные символы"); }
		}

		return m_content;
	}
}