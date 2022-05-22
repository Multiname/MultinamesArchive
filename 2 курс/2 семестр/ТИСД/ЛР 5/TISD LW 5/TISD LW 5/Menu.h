#pragma once
#include "BMP.h"

namespace LW_5
{
	class Menu
	{
	public:
		Menu();
		Menu(std::string inputFile, std::string errorFile = "Errors.txt");
		~Menu();

		void Run();

	private:
		void Pause();

		BMP* _bmp{};
		std::string _image{};
		std::string _errorFile{};
	};
}