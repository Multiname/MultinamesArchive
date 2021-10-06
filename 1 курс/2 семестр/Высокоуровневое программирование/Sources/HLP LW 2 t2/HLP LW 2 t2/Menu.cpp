#include "Menu.h"
#include <iostream>
#include "TypeDefinitions.h"
#include "UserInput.h"

using namespace KMK;

Menu::Menu(std::string title, MenuItem** items, size_t count)
{
	m_title = title;
	m_items = items;
	m_count = count;
}

int Menu::GetSelect() { return m_select; }
bool Menu::GetRunning() { return m_running; }
std::string Menu::GetTitle() { return m_title; }
size_t Menu::GetCount() { return m_count; }
MenuItem** Menu::GetItems() { return m_items; }

void Menu::Print() const
{
	std::cout << '\t' << m_title << "\n\n";
	for (Iteration i = 0; i < m_count; i++)
	{
		std::cout << i << ". ";
		m_items[i]->PrintItemName();
		std::cout << '\n';
	}
}

int Menu::RunCommand() const
{
	Print();
	std::cout << m_count << ". Exit\n";
	std::cout << ">>> ";
	UserInput input{};
	std::cin >> input;
	try
	{
		uint16_t command = input.GetUInt16(0, m_count);
		system("cls");
		if (command != m_count)
		{
			return m_items[command]->Run();
		}
		else
		{
			return 1;
		}
	}
	catch (StringToUInt16Exception& exception)
	{
		std::cout << exception.GetError() << "\n";
		std::cin >> input;
		return 0;
	}
}

std::ostream& KMK::operator<<(std::ostream& out, const Menu& menu)
{
	menu.Print();

	return out;
}

std::istream& KMK::operator>>(std::istream& in, const Menu& menu)
{
	int code = 0;
	while (code == 0)
	{
		code = menu.RunCommand();
		system("cls");
	}

	return in;
}