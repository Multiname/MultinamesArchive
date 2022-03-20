#include "Real.h"
#include <iostream>

int main()
{
	std::cout << "Divisible = ";
	std::string divisibleInput{};
	std::getline(std::cin, divisibleInput);

	std::cout << "Divisor = ";
	std::string divisorInput{};
	std::getline(std::cin, divisorInput);

	Real::Real divisible{ divisibleInput };
	Real::Real divisor{ divisorInput };

	try
	{
		std::cout << divisible.ToString() << " : " << divisor.ToString()
			<< " = " << divisible.Divide(divisor)->ToString() << "\n";
	}
	catch (Real::DivisionByZeroException& error)
	{
		std::cout << error.GetError() << "\n";
	}

	return 0;
}