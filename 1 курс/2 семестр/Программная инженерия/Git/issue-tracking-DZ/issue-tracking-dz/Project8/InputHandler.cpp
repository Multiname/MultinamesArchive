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
			InputException("������ ��� ����� �����, ������� ���� (1-2 �����)", "������ ������"); }
		if (m_content.size() > 2) { throw
			InputException("���������� �������� ������ 2, ���������� ������ ���� ��� ��� (1-2 �����)",
			"������� ����� ��������"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("� ��������� ������ ������������ �������, �� ���������� �������, ���������� ������ ���� ��� ��� (1-2 �����)",
					"������� �� �������� �������"); }
			if (!isdigit(m_content[i])) { throw
				InputException("� ��������� ������ ������������ �������, �� ���������� �������, ���������� ������ ���� ��� ��� (1-2 �����)",
				"������� �� �������� �������"); }
		}

		unsigned short day = std::stoi(m_content);
		if (day > 31) { throw InputException("���� ������ �����������, ����� �� ����� ���� ������ 31",
			"������� ������� �����"); }
		if (day == 0) { throw InputException("���� ������ �����������, ����� �� ����� ��������� 0",
			"������� ��������� �����"); }

		return day;
	}

	unsigned short InputHandler::GetMonth()
	{
		if (m_content.size() == 0) { throw InputException("������ ��� ����� �����, ������� ����� (1-2 �����)",
			"������ ������"); }
		if (m_content.size() > 2) { throw
			InputException("���������� �������� ������ 2, ���������� ������ ����� ��� ��� (1-2 �����)",
			"������� ����� ��������"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("� ��������� ������ ������������ �������, �� ���������� �������, ���������� ������ ����� ��� ��� (1-2 �����)",
					"������� �� �������� �������");	}
			if (!isdigit(m_content[i])) { throw
				InputException("� ��������� ������ ������������ �������, �� ���������� �������, ���������� ������ ����� ��� ��� (1-2 �����)",
						"������� �� �������� �������"); }
		}

		unsigned short month = std::stoi(m_content);
		if (month > 12) { throw InputException("����� ������ �����������, ����� �� ����� ���� ������ 12",
			"������� ������� �����"); }
		if (month == 0) { throw InputException("����� ������ �����������, ����� �� ����� ��������� 0",
			"������� ��������� �����"); }

		return month;
	}

	unsigned short InputHandler::GetYear()
	{
		if (m_content.size() == 0) { throw InputException("������ ��� ����� �����, ������� ��� (4 �����)",
			"������ ������"); }
		if (m_content.size() != 4) { throw InputException("���������� �������� �� ����� 4, ���������� ������ ��� ��� ��� ",
			"�������� ����� ��������"); }
		if (m_content[0] < 0 || m_content[0] > 255 || m_content[1] < 0 || m_content[1] > 255 ||
			m_content[2] < 0 || m_content[2] > 255 || m_content[3] < 0 || m_content[3] > 255) { throw
			InputException("� ��������� ������ ������������ �������, �� ���������� �������, ���������� ������ ��� ��� ��� (4 �����)",
				"������� �� �������� �������"); }
		if (!isdigit(m_content[0]) || !isdigit(m_content[1]) || !isdigit(m_content[2]) || !isdigit(m_content[3]))
		{ throw InputException("� ��������� ������ ������������ �������, �� ���������� �������, ���������� ������ ��� ��� ��� (4 �����)", 
			"������� �� �������� �������"); }

		return std::stoi(m_content);
	}

	std::string InputHandler::GetLogin()
	{
		if (m_content.size() < 5) { throw InputException("������� ���� ��������, ������� ����� ��� ��� (5-20 ��������)",
				"������� ���� ��������"); }
		if (m_content.size() > 20) { throw InputException("������� ����� ��������, ������� ����� ��� ��� (5-20 ��������)",
				"������� ����� ��������"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("� ������ ������������ �������� �������, ����������� ������ ���������� ����� � �����",
					"�������� �������"); }
			if (!isalpha(m_content[i]) && !isdigit(m_content[i])) { throw
				InputException("� ������ ������������ �������� �������, ����������� ������ ���������� ����� � �����",
					"�������� �������"); }
		}

		return m_content;
	}

	std::string InputHandler::GetPassword()
	{
		if (m_content.size() < 5) { throw InputException("������� ���� ��������, ������� ������ ��� ��� (5-20 ��������)",
				"������� ���� ��������"); }
		if (m_content.size() > 20) { throw InputException("������� ����� ��������, ������� ������ ��� ��� (5-20 ��������)",
				"������� ����� ��������"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("� ������ ������������ �������� �������, ����������� ������ ���������� ����� � �����",
					"�������� �������"); }
			if (!isalpha(m_content[i]) && !isdigit(m_content[i])) { throw
				InputException("� ������ ������������ �������� �������, ����������� ������ ���������� ����� � �����",
					"�������� �������"); }
		}

		return m_content;
	}

	std::string InputHandler::GetNickname()
	{
		if (m_content.size() < 5) { throw InputException("������� ���� ��������, ������� ��� ��� ��� (5-40 ��������)",
				"������� ���� ��������"); }
		if (m_content.size() > 40) { throw InputException("������� ����� ��������, ������� ��� ��� ��� (5-40 ��������)",
				"������� ����� ��������"); }
		if (m_content[0] == ' ' || m_content[m_content.size() - 1] == ' ') { throw
			InputException("� ����� ��� ������ ����� ����� ������, �� ����� ���������� ������ ������",
					"������ � ����� ��� ������"); }
		if (m_content[0] == '.') { throw
			InputException("� ������ ����� ����� �����, ��� ����� ���������� ������ ������ ��� �� �����",
					"����� � ������"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("� ����� ������ ������������ ����, ����������� ���������� ����",
					"�������� ����"); }
			if (!isalpha(m_content[i]) && m_content[i] != ' ' && m_content[i] != '.') { throw 
				InputException("� ����� ������� ������������ �������, ����������� ������ ���������� �����, ����� � �������",
					"�������� �������"); }
			if (m_content[i] == ' ' && m_content[i + 1] == ' ') { throw
				InputException("� ����� ����������� 2 ������� ������, ���������� ��� ���",
					"������� ������"); }
			if (m_content[i] == '.' && m_content[i + 1] == '.') { throw
				InputException("� ����� ����������� 2 ����� ������, ���������� ��� ���",
					"��� ����� ������"); }
		}

		return m_content;
	}

	unsigned long InputHandler::GetCost()
	{
		if (m_content.size() == 0) { throw InputException("������ ��� ����� �����, ������� ����",
			"������ ������"); }
		if (m_content.size() > 10) { throw
			InputException("������� ����� ��������, ������� ���� ��� ���",
				"������� ����� ��������"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("������������ �������� �������, ���� ����� ��������� ������ �����",
					"�������� �������"); }
			if (!isdigit(m_content[i])) { throw
				InputException("������������ �������� �������, ���� ����� ��������� ������ �����",
					"�������� �������"); }
		}

		unsigned long cost{};
		try
		{
			cost = std::stoul(m_content);
		}
		catch (std::out_of_range)
		{
			throw InputException("������� ������� �����, ������� ���� ��� ���",
				"������� ������� �����");
		}

		return cost;
	}

	std::string InputHandler::GetSquare()
	{
		if (m_content.size() == 0) { throw InputException("������ ��� ����� �����, ������� �������",
			"������ ������"); }
		if (m_content.size() > 3) { throw
			InputException("������� ����� ��������, ������� ������� ��� ���",
				"������� ����� ��������"); }
		for (unsigned short i{}; i < m_content.size(); ++i)
		{
			if (m_content[i] < 0 || m_content[i] > 255) { throw
				InputException("������������ �������� �������, ������� ����� ��������� ������ �����",
					"�������� �������"); }
			if (!isdigit(m_content[i])) { throw
				InputException("������������ �������� �������, ������� ����� ��������� ������ �����",
					"�������� �������"); }
		}

		return m_content;
	}
}