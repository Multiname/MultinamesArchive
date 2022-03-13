#pragma once
#include <string>

namespace Real
{
	class Real
	{
	public:
		Real();
		Real(std::string number);
		Real(Real& real);
		~Real();

		std::string ToString();
		Real* MultiplyByInt(int number);
		short CompareAbs(Real number);
		Real* SubtractLessPlus(Real number);

	private:
		void IncDegree();
		void DecDegree();
		void IncreaseDegreeByUint(unsigned short number);
		void DecreaseDegreeByUint(unsigned short number);
		void DecreaseDegree(int* value, unsigned short size);
		short CompareDegree(int* value, unsigned short size);
		int* CopyDegree();

		const unsigned short _MaxMantissaLength = 30;
		const unsigned short _MaxDegreeLength = 5;
		const unsigned short _Base = 10;

		int* _degreeShift{};

		bool _sign{};
		int* _mantissa{};
		int* _degree{};
	};
}