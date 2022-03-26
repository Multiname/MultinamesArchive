#include "Menu.h"
#include <fstream>
#include <iostream>

namespace DTAS
{
	Menu::Menu() : _output("Output.txt"), _logFile("Log.txt"), _tree() {}

	Menu::Menu(std::string input, std::string output,
		std::string logFile) : _output(output), _logFile(logFile)
	{
		std::ifstream inputData(input);
		if (inputData)
			_tree.Create(inputData);
		else
		{
			std::ofstream errorData(_logFile, std::ios_base::app);
			errorData << "Input file wasn't found\n";
			errorData.close();

			std::cout << "Input file wasn't found";
			Pause();
		}
		inputData.close();
	}

	void Menu::Run()
	{
		unsigned short input = 1;
		while (input != 0)
		{
			system("cls");
			_tree.Print();

			std::cout << "\n1. Create tree\n";
			std::cout << "2. Delete tree\n\n";

			std::cout << "3. Change element\n";
			std::cout << "4. Insert element\n";
			std::cout << "5. Remove element\n\n";

			std::cout << "6. Bypass directly\n";
			std::cout << "7. Bypass symmetrical\n";
			std::cout << "8. Bypass conversely\n\n";

			std::cout << "9. Form expression directly\n";
			std::cout << "10. Form expression symmetrical\n";
			std::cout << "11. Form expression conversely\n\n";

			std::cout << "0. Exit\n";
			std::cout << ">>> ";
			std::cin >> input;
			std::cout << "\n";

			std::string result{};
			switch (input)
			{
			case 1:
				system("cls");
				_tree.Clear();
				_tree.Create();
				break;
			case 2:
				_tree.Clear();
				break;
			case 3:
				system("cls");
				_tree.Change();
				break;
			case 4:
				system("cls");
				_tree.Insert();
				break;
			case 5:
				system("cls");
				_tree.Remove();
				break;
			case 6:
				_tree.BypassDirectly();
				if (!_tree.IsEmpty())
					Pause();
				break;
			case 7:
				_tree.BypassSymmetrical();
				if (!_tree.IsEmpty())
					Pause();
				break;
			case 8:
				_tree.BypassConversely();
				if (!_tree.IsEmpty())
					Pause();
				break;
			case 9:
				result = _tree.GetExpressionDirectly();
				std::cout << result;
				if (!_tree.IsEmpty())
				{
					std::ofstream outputData(_output);
					outputData << result;
					outputData.close();
					Pause();
				}
				break;
			case 10:
				result = _tree.GetExpressionSymmetrical();
				std::cout << result;
				if (!_tree.IsEmpty())
				{
					std::ofstream outputData(_output);
					outputData << result;
					outputData.close();
					Pause();
				}
				break;
			case 11:
				result = _tree.GetExpressionConversely();
				std::cout << result;
				if (!_tree.IsEmpty())
				{
					std::ofstream outputData(_output);
					outputData << result;
					outputData.close();
					Pause();
				}
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