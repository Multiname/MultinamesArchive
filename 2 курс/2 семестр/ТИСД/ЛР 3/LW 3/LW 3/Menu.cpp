#include "Menu.h"

namespace DTAS
{
	Menu::Menu() : _graph() {}

	Menu::Menu(std::string inputFile) : _graph(inputFile), _logFile("Log.txt") {}

	Menu::Menu(std::string inputFile, std::string outputFile) : Menu(inputFile, outputFile, "Log.txt") {}

	Menu::Menu(std::string inputFile, std::string outputFile, std::string logFile) : _graph(inputFile, outputFile), _logFile(logFile) {}

	Menu::~Menu() { remove("pauseTemp"); }

	void Menu::Run()
	{
		int command = 1;

		while (command != 0)
		{
			system("cls");
			_graph.Print(3);

			std::cout << "\n1. Add element\n";
			std::cout << "2. Change connection\n";
			std::cout << "3. Remove element\n";
			std::cout << "4. Clear\n";
			std::cout << "\n5. Depth-first search\n";
			std::cout << "6. Breadth-first search\n";
			std::cout << "7. Show max distances\n";
			std::cout << "\n0. Exit\n";
			std::cout << ">>> ";
			std::cin >> command;
			std::cout << "\n";

			std::string input{};
			std::string source{};
			std::string destination{};
			switch (command)
			{
			case 1:
				std::cout << "Input new element: ";
				std::cin >> input;
				_graph.Add(input);
				break;
			case 2:
				std::cout << "Input source: ";
				std::cin >> source;
				std::cout << "Input destination: ";
				std::cin >> destination;
				std::cout << "Input new weight or '-' to break the connection: ";
				std::cin >> input;
				try
				{
					_graph.Connect(source, destination, input);
				}
				catch (IncorrectWeightException& error)
				{
					std::ofstream file(_logFile, std::ios_base::app);
					std::cout << error.GetError() << "\n";
					file << error.GetError() << "\n";
					file.close();
					Pause();
				}
				break;
			case 3:
				std::cout << "Input element to remove: ";
				std::cin >> input;
				_graph.Remove(input);
				break;
			case 4:
				_graph.Clear();
				break;
			case 5:
				std::cout << "Input start element: ";
				std::cin >> input;
				std::cout << "DFS: ";
				_graph.DFS(input);
				Pause();
				break;
			case 6:
				std::cout << "Input start element: ";
				std::cin >> input;
				std::cout << "BFS: ";
				_graph.BFS(input);
				Pause();
				break;
			case 7:
				std::cout << "Max distances:\n";
				_graph.PrintMaxDistances(3);
				Pause();
				break;
			}
		}
	}

	void Menu::Pause()
	{
		system("pause>pauseTemp");
		remove("pauseTemp");
	}
}