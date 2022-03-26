#pragma once
#include "ExpressionTree.h"

namespace DTAS
{
	class Menu
	{
	public:
		Menu();
		Menu(std::string input,
			std::string output = "Output.txt",
			std::string logFile = "Log.txt");

		void Run();

	private:
		void Pause();

		std::string _output{};
		std::string _logFile{};

		ExpressionTree _tree{};
	};
}