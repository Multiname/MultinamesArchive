#include "Menu.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		DTAS::Menu menu{ "Input.txt" };
		menu.Run();
	}
	else if (argc == 2)
	{
		DTAS::Menu menu{ argv[1] };
		menu.Run();
	}
	else if (argc == 3)
	{
		DTAS::Menu menu{ argv[1], argv[2] };
		menu.Run();
	}
	else
	{
		DTAS::Menu menu{ argv[1], argv[2], argv[3] };
		menu.Run();
	}

	return 0;
}