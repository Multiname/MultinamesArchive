#pragma once
#include <string>

namespace Real
{
	class Real
	{
	public:
		Real();
		Real(std::string sign, std::string mantissa, std::string degree);
		Real(std::string number);
		Real(Real& real);
		~Real();

		std::string ToString();;
		Real* Divide(Real number);

	private:
		void IncDegree();
		void DecDegree();
		void DecreaseDegree(int* value, unsigned short size);
		void IncreaseDegree(int* value, unsigned short size);
		short CompareDegree(int* value, unsigned short size);
		int* CopyDegree();

		static const struct Constants
		{
			Constants()
			{
				for (unsigned short i{}; i < MaxDegreeLength - 1; ++i)
					DegreeShift[i] = Base - 1;
				DegreeShift[MaxDegreeLength - 1] = (Base - 1) / 2;
			}

			static const unsigned short MaxMantissaLength = 30;
			static const unsigned short MaxDegreeLength = 5;
			static const unsigned short Base = 10;

			int DegreeShift[MaxDegreeLength];
		} _Constants;

		bool _sign{};
		int* _mantissa{};
		int* _degree{};
	};

	class DivisionByZeroException
	{
	public:
		DivisionByZeroException(std::string error);
		std::string GetError();

	private:
		std::string _error{};
	};
}