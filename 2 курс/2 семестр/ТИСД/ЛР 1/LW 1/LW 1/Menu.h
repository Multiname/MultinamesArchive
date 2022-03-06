#pragma once
#include "List.h"

namespace DTAS
{
	class Menu
	{
	public:
		Menu();
		Menu(std::string input, std::string output, std::string logFile);

		void Start();

	private:
		std::string _output{};
		std::string _logFile{};
		List _list{};

		void ShowMenu();
		void ShowList();
		void Add();
		void Remove();
		void Find();
		void Clear();
		void RunTask();
		void MoveForward();
		void ReturnBack();
	};
}