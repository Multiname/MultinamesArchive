#include <fstream>
using namespace std;

void minusone(ifstream& in)
{
	char c;
	in.read((char*)&c, sizeof(c));
	if (in.tellg() != -1)
	{
		int x = sizeof(c);
		in.seekg(-x, ios::cur);
	}
}