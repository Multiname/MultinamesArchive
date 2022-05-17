#pragma once
#include "Knuth.h"

namespace LW_4
{
	class Menu
	{
	public:
		Menu();
		Menu(std::string inputFile, std::string saveFile = "Output.txt");
		~Menu();

		void Run();

	private:
		void Pause();

		Knuth _knuth{};
	};
}