#include "Menu.h"
#include <iostream>

namespace LW_4
{
	Menu::Menu() : _knuth() {}
	Menu::Menu(std::string inputFile, std::string saveFile) :
		_knuth(inputFile, saveFile) {}
	Menu::~Menu() { remove("pauseTemp"); }

	void Menu::Run()
	{
		uint16_t command = 1;

		while (command != 0)
		{
			_knuth.Restore();
			std::cout << "\n";
			_knuth.Print();
			std::cout << "\n";

			std::cout << "1. Replace columns\n";
			std::cout << "2. Show number at position\n";
			std::cout << "0. Exit\n";
			std::cout << ">>> ";
			std::cin >> command;
			std::cout << "\n";

			if (command == 1)
			{
				std::cout << "Input first column: ";
				uint16_t firstColumn;
				std::cin >> firstColumn;

				std::cout << "Input second column: ";
				uint16_t secondColumn;
				std::cin >> secondColumn;

				_knuth.ReplaceColumns(firstColumn, secondColumn);
			}
			else if (command == 2)
			{
				std::cout << "i: ";
				uint16_t i;
				std::cin >> i;

				std::cout << "j: ";
				uint16_t j;
				std::cin >> j;

				std::cout << "Number: ";
				_knuth.ShowNumberAtPosition(i, j);
				std::cout << "\n";
				Pause();
			}

			system("cls");
		}
	}

	void Menu::Pause()
	{
		system("pause>pauseTemp");
		remove("pauseTemp");
	}
}