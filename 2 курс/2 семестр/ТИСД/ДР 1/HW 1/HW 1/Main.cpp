#include "Real.h"
#include <iostream>

int main()
{
	std::cout << "Sign (+/-): ";
	std::string sign{};
	std::getline(std::cin, sign);

	std::cout << "Mantissa (m.n): ";
	std::string mantissa{};
	std::getline(std::cin, mantissa);

	std::cout << "Degree: ";
	std::string degree{};
	std::getline(std::cin, degree);

	Real::Real divisible{ sign, mantissa, degree };

	std::cout << "Sign (+/-): ";
	std::getline(std::cin, sign);

	std::cout << "Mantissa (m.n): ";
	std::getline(std::cin, mantissa);

	std::cout << "Degree: ";
	std::getline(std::cin, degree);

	Real::Real divisor{ sign, mantissa, degree };

	//std::cout << "Divisible = ";
	//std::string divisibleInput{};
	//std::getline(std::cin, divisibleInput);

	//std::cout << "Divisor = ";
	//std::string divisorInput{};
	//std::getline(std::cin, divisorInput);

	//Real::Real divisible{ divisibleInput };
	//Real::Real divisor{ divisorInput };

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