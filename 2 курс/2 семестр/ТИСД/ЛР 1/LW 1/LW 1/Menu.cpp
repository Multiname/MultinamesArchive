#include "Menu.h"
#include <iostream>
#include <fstream>

namespace DTAS
{
	Menu::Menu(): _output("Output.txt"), _logFile("Log.txt"), _list() {}

	Menu::Menu(std::string input, std::string output, std::string logFile) :
		_output(output), _logFile(logFile)
	{
		std::ifstream inputData(input);
		unsigned short number;
		inputData >> number;
		std::vector<float> data{};
		for (unsigned short i{}; i < number; ++i)
		{
			float element;
			inputData >> element;
			data.push_back(element);
		}
		inputData.close();

		_list = List(data);
	}

	void Menu::Start()
	{
		unsigned short command = 1;
		while (command != 0)
		{
			system("cls");
			ShowList();
			std::cout << "\n";
			ShowMenu();
			std::cin >> command;
			std::cout << "\n";

			switch (command)
			{
			case 1:
				Add();
				break;
			case 2:
				Remove();
				break;
			case 3:
				Find();
				break;
			case 4:
				Clear();
				break;
			case 5:
				RunTask();
				break;
			case 6:
				MoveForward();
				break;
			case 7:
				ReturnBack();
				break;
			}
		}
	}

	void Menu::ShowMenu()
	{
		std::cout << "1. Add element\n";
		std::cout << "2. Remove element\n";
		std::cout << "3. Find element\n";
		std::cout << "4. Clear list\n";
		std::cout << "5. Run task\n";
		std::cout << "6. Move forward\n";
		std::cout << "7. Return back\n";
		std::cout << "0. Exit\n";
		std::cout << ">>> ";
	}

	void Menu::ShowList()
	{
		std::vector<float> data = _list.GetData();
		if (data.size() == 0)
		{
			std::cout << "List is empty\n";
		}
		else
		{
			int currentPosition = _list.GetCurrentPosition();
			for (unsigned short i{}; i < data.size(); ++i)
			{
				std::cout << i << ". ";
				if (i == currentPosition)
				{
					std::cout << ">";
				}
				else
				{
					std::cout << " ";
				}
				std::cout << " " << data[i] << "\n";
			}
		}
	}

	void Menu::Add()
	{
		if (_list.IsEmpty())
		{
			std::cout << "Number: ";
			float number;
			std::cin >> number;

			_list.AppendHead(number);
		}
		else
		{
			unsigned short mode;
			std::cout << "0. Add before\n";
			std::cout << "1. Add after\n";
			std::cout << ">>> ";
			std::cin >> mode;

			if (mode != 0 && mode != 1)
			{
				std::cout << "Input error\n";
				return;
			}

			std::cout << "\nNumber: ";
			float number;
			std::cin >> number;

			try
			{
				if (mode == 0)
				{
					_list.AppendBefore(number);
				}
				else if (mode == 1)
				{
					_list.AppendAfter(number);
				}
			}
			catch (ElementAccessException& error)
			{
				std::cout << error.GetError() << "\n";
				std::ofstream errorData(_logFile, std::ios_base::app);
				errorData << "Adding error\n";
				errorData.close();
				system("pause");
			}
		}
	}

	void Menu::Remove()
	{
		try
		{
			_list.Remove();
		}
		catch (ElementAccessException& error)
		{
			std::cout << error.GetError() << "\n";
			std::ofstream errorData(_logFile, std::ios_base::app);
			errorData << "Removing error\n";
			errorData.close();
			system("pause");
		}
	}

	void Menu::Find()
	{
		std::cout << "Number: ";
		float number;
		std::cin >> number;

		if (!_list.FindAndSet(number))
		{
			std::cout << "Number wasn't found\n";
			system("pause");
		}
	}

	void Menu::Clear()
	{
		_list.Clear();
	}

	void Menu::RunTask()
	{
		if (!_list.IsEmpty())
		{
			ReturnBack();
			List newList{};
			while (_list.GetCurrentPosition() != -1)
			{
				float number = _list.GetCurrentElement();
				if (number < 0)
				{
					if (newList.IsEmpty())
					{
						newList.AppendHead(number);
					}
					else
					{
						newList.AppendAfter(number);
						newList.MoveForward();
					}
				}
				_list.MoveForward();
			}

			ReturnBack();
			while (_list.GetCurrentPosition() != -1)
			{
				float number = _list.GetCurrentElement();
				if (number >= 0)
				{
					if (newList.IsEmpty())
					{
						newList.AppendHead(number);
					}
					else
					{
						newList.AppendAfter(number);
					}
				}
				_list.MoveForward();
			}
			
			std::vector<float> data = newList.GetData();
			std::ofstream outputData(_output);
			if (data.size() == 0)
			{
				std::cout << "List is empty\n";
			}
			else
			{
				for (unsigned short i{}; i < data.size(); ++i)
				{
					std::cout << i << ".   " << data[i] << "\n";
					outputData << data[i] << " ";
				}
			}

			outputData.close();
			ReturnBack();
			std::cout << "\n";
			system("pause");
		}
	}

	void Menu::MoveForward()
	{
		_list.MoveForward();
	}

	void Menu::ReturnBack()
	{
		_list.ReturnBack();
	}
}