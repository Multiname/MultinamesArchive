#pragma once
#include "Graph.h"

namespace DTAS
{
	class Menu
	{
	public:
		Menu();
		Menu(std::string inputFile);
		Menu(std::string inputFile, std::string outputFile);
		Menu(std::string inputFile, std::string outputFile, std::string logFile);
		~Menu();

		void Run();

	private:
		void Pause();

		Graph<std::string> _graph{};
		std::string _logFile{};
	};
}