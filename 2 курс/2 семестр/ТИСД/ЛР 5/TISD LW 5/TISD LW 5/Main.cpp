#include "Menu.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cout << "Too few arguments\n";
	}
	else if (argc == 2)
	{
		try
		{
			LW_5::Menu menu{ argv[1] };
			menu.Run();
		}
		catch (const std::exception&)
		{
			return 1;
		}
	}
	else if (argc == 3)
	{
		try
		{
			LW_5::Menu menu{ argv[1], argv[2] };
			menu.Run();
		}
		catch (const std::exception&)
		{
			return 1;
		}
	}

	return 0;
}