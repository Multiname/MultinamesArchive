#include "Menu.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		DTAS::Menu menu{};
		menu.Start();
	}
	if (argc == 4)
	{
		DTAS::Menu menu{ argv[1], argv[2], argv[3] };
		menu.Start();
	}
	else
	{
		std::cout << "Too few arguments\n";
	}

	return 0;
}