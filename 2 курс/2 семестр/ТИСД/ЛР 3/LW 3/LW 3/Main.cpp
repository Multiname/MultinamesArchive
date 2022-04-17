#include "Menu.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		DTAS::Menu menu{};
		menu.Run();
	}
	else
	{
		try
		{
			if (argc == 2)
			{
				DTAS::Menu menu(argv[1]);
				menu.Run();
			}
			else if (argc == 3)
			{
				DTAS::Menu menu(argv[1], argv[2]);
				menu.Run();
			}
			else if (argc == 4)
			{
				DTAS::Menu menu(argv[1], argv[2], argv[3]);
				menu.Run();
			}
		}
		catch (DTAS::IncorrectWeightException& error)
		{
			std::ofstream file("Log.txt", std::ios_base::app);
			std::cout << error.GetError() << "\n";
			file << error.GetError() << "\n";
			file.close();
		}
	}

	return 0;
}