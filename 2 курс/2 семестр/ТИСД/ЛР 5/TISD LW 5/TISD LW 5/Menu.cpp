#include "Menu.h"
#include <iostream>
#include <fstream>

namespace LW_5
{
	Menu::Menu() : _bmp(nullptr), _image{}, _errorFile("Errors.txt") {}
	Menu::Menu(std::string inputFile, std::string errorFile) :
		_image(inputFile), _errorFile(errorFile)
	{
		try
		{
			_bmp = new BMP(inputFile);
		}
		catch (const std::exception& ex)
		{
			std::ofstream errorData(_errorFile, std::ios_base::app);
			errorData << ex.what() << "\n";
			errorData.close();

			std::cout << ex.what() << "\n";
			Pause();

			throw ex;
		}
	}
	Menu::~Menu() { remove("pauseTemp"); }

	void Menu::Run()
	{
		uint16_t command = 1;

		while (command != 0)
		{
			system("cls");

			std::cout << "Image: " << _image << "\n";
			std::cout << "Height: " << _bmp->getHeight() << " px\n";
			std::cout << "Width: " << _bmp->getWidth() << " px\n";
			std::cout << "Image size: " << _bmp->getSizeImage() << " B\n\n";

			std::cout << "1. Change image\n";
			std::cout << "0. Exit\n";
			std::cout << ">>> ";
			std::cin >> command;
			std::cout << "\n";

			if (command == 1)
			{
				std::cout << "Input image path: ";
				std::string path;
				std::cin.ignore();
				std::getline(std::cin, path);
				try
				{
					_bmp->load(path);
				}
				catch (const std::exception& ex)
				{
					std::ofstream errorData(_errorFile, std::ios_base::app);
					errorData << ex.what() << "\n";
					errorData.close();

					std::cout << ex.what() << "\n";
					Pause();
				}
			}
		}
	}

	void Menu::Pause()
	{
		system("pause>pauseTemp");
		remove("pauseTemp");
	}
}