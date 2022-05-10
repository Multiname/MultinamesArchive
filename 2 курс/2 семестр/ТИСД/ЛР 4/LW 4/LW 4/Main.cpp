#include "Knuth.h"

int main()
{
	LW_4::Knuth knuth("Input.txt");
	knuth.Print();
	knuth.ReplaceColumns(2, 4);
	knuth.Print();

	return 0;
}