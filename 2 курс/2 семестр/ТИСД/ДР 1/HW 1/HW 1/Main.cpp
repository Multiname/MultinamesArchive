#include "Real.h"

#include <iostream>

int main()
{
	Real::Real a1{"200"};
	Real::Real b1{"100"};
	std::cout << a1.ToString() << " - " << b1.ToString() << " = " << a1.SubtractLessPlus(b1)->ToString() << "\n";

	Real::Real a2{ "320" };
	Real::Real b2{ "100" };
	std::cout << a2.ToString() << " - " << b2.ToString() << " = " << a2.SubtractLessPlus(b2)->ToString() << "\n";

	Real::Real a3{ "300" };
	Real::Real b3{ "120" };
	std::cout << a3.ToString() << " - " << b3.ToString() << " = " << a3.SubtractLessPlus(b3)->ToString() << "\n";

	Real::Real a4{ "100" };
	Real::Real b4{ "10" };
	std::cout << a4.ToString() << " - " << b4.ToString() << " = " << a4.SubtractLessPlus(b4)->ToString() << "\n";

	Real::Real a5{ "120" };
	Real::Real b5{ "20" };
	std::cout << a5.ToString() << " - " << b5.ToString() << " = " << a5.SubtractLessPlus(b5)->ToString() << "\n";

	Real::Real a6{ "100" };
	Real::Real b6{ "23" };
	std::cout << a6.ToString() << " - " << b6.ToString() << " = " << a6.SubtractLessPlus(b6)->ToString() << "\n";

	return 0;
}