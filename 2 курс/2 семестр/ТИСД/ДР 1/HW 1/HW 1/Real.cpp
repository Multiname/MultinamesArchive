#include "Real.h"

namespace Real
{
	Real::Constants const Real::_Constants;

	Real::Real() : _sign(false), _mantissa(new int[_Constants.MaxMantissaLength]{}),
		_degree(new int[_Constants.MaxDegreeLength]{}) {}

	Real::Real(std::string number)
	{
		_mantissa = new int[_Constants.MaxMantissaLength] {};
		_degree = new int[_Constants.MaxDegreeLength] {};
		for (unsigned short i{}; i < _Constants.MaxDegreeLength; ++i)
			_degree[i] = _Constants.DegreeShift[i];

		unsigned short* temp = new unsigned short[_Constants.MaxMantissaLength] {};
		int t = 0;
		bool isPointReached = false;
		bool isNotZeroReached = false;
		for (unsigned short i{}; i < number.length(); ++i)
		{
			if ('1' <= number[i] && number[i] <= '9')
			{
				temp[t] = number[i] - '0';

				isNotZeroReached = true;
				if (!isPointReached)
					IncDegree();

				++t;
			}
			else if (number[i] == '0')
			{
				temp[t] = 0;

				if (isPointReached && !isNotZeroReached)
					DecDegree();
				else if (!isPointReached && isNotZeroReached)
					IncDegree();

				++t;
			}
			else if (number[i] == '-')
				_sign = true;
			else if (number[i] == '.')
				isPointReached = true;
		}

		if (isNotZeroReached)
		{
			unsigned short i = 0;
			--t;
			while (temp[t] == 0)
				--t;
			while (t >= 0)
			{
				_mantissa[i] = temp[t];
				--t;
				++i;
			}

			DecDegree();
		}
		else
			_sign = false;

		delete[] temp;
	}

	Real::Real(Real& real) : _sign(real._sign)
	{
		_degree = new int[_Constants.MaxDegreeLength] {};
		_mantissa = new int[_Constants.MaxMantissaLength] {};

		for (unsigned short i{}; i < _Constants.MaxDegreeLength; ++i)
			_degree[i] = real._degree[i];
		for (unsigned short i{}; i < _Constants.MaxMantissaLength; ++i)
			_mantissa[i] = real._mantissa[i];
	}

	Real::~Real()
	{
		delete[] _mantissa;
		delete[] _degree;
	}

	std::string Real::ToString()
	{
		std::string number = "";
		if (_sign)
			number += '-';

		int pos = -1;
		for (int i = _Constants.MaxMantissaLength - 1; i >= 0; --i)
			if (_mantissa[i] != 0)
			{
				pos = i;
				break;
			}

		if (pos == -1)
		{
			number += "0.0 E 0";
			return number;
		}
		else
		{
			number += "0.";
			for (; pos >= 0; --pos)
			{
				number += (_mantissa[pos] + '0');
			}
		}

		number += " E ";
		
		int* temp = CopyDegree();
		IncDegree();

		if (CompareDegree((int*)_Constants.DegreeShift, _Constants.MaxDegreeLength) == 1)
		{
			number += "-";

			for (unsigned short i{}; i < _Constants.MaxDegreeLength; ++i)
				_degree[i] = _Constants.DegreeShift[i];

			DecreaseDegree(temp, _Constants.MaxDegreeLength);
			DecDegree();

			int i = _Constants.MaxDegreeLength - 1;
			while (_degree[i] == 0)
				--i;
			for (; i >= 0; --i)
				number += (_degree[i] + '0');
		}
		else if (CompareDegree((int*)_Constants.DegreeShift, _Constants.MaxDegreeLength) == -1)
		{
			DecreaseDegree((int*)_Constants.DegreeShift, _Constants.MaxDegreeLength);

			int i = _Constants.MaxDegreeLength - 1;
			while (_degree[i] == 0)
				--i;
			for (; i >= 0; --i)
				number += (_degree[i] + '0');
		}
		else
			number += '0';
		delete[] _degree;
		_degree = temp;

		return number;
	}

	Real* Real::Divide(Real number)
	{
		bool dividedByZero = true;
		for (unsigned short i{}; i < _Constants.MaxMantissaLength; ++i)
			if (number._mantissa[i] != 0)
			{
				dividedByZero = false;
				break;
			}
		if (dividedByZero)
			throw DivisionByZeroException("Division by zero");

		bool divisibleIsZero = true;
		for (unsigned short i{}; i < _Constants.MaxMantissaLength; ++i)
			if (_mantissa[i] != 0)
			{
				divisibleIsZero = false;
				break;
			}
		if (divisibleIsZero)
			return new Real();

		int* degree{};
		if (CompareDegree(number._degree, _Constants.MaxDegreeLength) == -1)
		{
			int* temp = CopyDegree();

			DecreaseDegree(number._degree, _Constants.MaxDegreeLength);
			IncreaseDegree((int*)_Constants.DegreeShift, _Constants.MaxDegreeLength);
			degree = CopyDegree();

			_degree = temp;
		}
		else if (CompareDegree(number._degree, _Constants.MaxDegreeLength) == 1)
		{
			number.DecreaseDegree(_degree, _Constants.MaxDegreeLength);
			number.IncreaseDegree((int*)_Constants.DegreeShift, _Constants.MaxDegreeLength);
			degree = number.CopyDegree();
		}
		else
		{
			degree = new int[_Constants.MaxDegreeLength] {};
			for (unsigned short i{}; i < _Constants.MaxDegreeLength; ++i)
				degree[i] = _Constants.DegreeShift[i];
		}

		unsigned short divisibleMantissaSize = _Constants.MaxMantissaLength;
		for (int i = _Constants.MaxMantissaLength - 1; i >= 0; --i)
			if (_mantissa[i] != 0)
				break;
			else
				--divisibleMantissaSize;

		unsigned short divisorMantissaSize = _Constants.MaxMantissaLength;
		for (int i = _Constants.MaxMantissaLength - 1; i >= 0; --i)
			if (number._mantissa[i] != 0)
				break;
			else
				--divisorMantissaSize;

		int* divisibleMantissa{};
		if (divisibleMantissaSize < divisorMantissaSize)
		{
			divisibleMantissa = new int[divisorMantissaSize] {};
			for (unsigned short i{}; i < divisibleMantissaSize; ++i)
				divisibleMantissa[i + divisorMantissaSize - divisibleMantissaSize] = _mantissa[i];
			divisibleMantissaSize = divisorMantissaSize;
		}
		else
		{
			divisibleMantissa = new int[divisibleMantissaSize] {};
			for (unsigned short i{}; i < divisibleMantissaSize; ++i)
				divisibleMantissa[i] = _mantissa[i];
		}

		int* num = new int[divisorMantissaSize] {};
		for (unsigned short i{}; i < divisorMantissaSize; ++i)
			num[divisorMantissaSize - i - 1] = divisibleMantissa[divisibleMantissaSize - i - 1];

		unsigned short numSize = divisorMantissaSize;
		unsigned short digitPosition = divisorMantissaSize;

		bool needExpansion = false;
		for (int i = divisorMantissaSize - 1; i >= 0; --i)
			if (num[i] < number._mantissa[i])
			{
				needExpansion = true;
				break;
			}
			else if (num[i] > number._mantissa[i])
				break;

		if (needExpansion)
		{
			int* temp = new int[numSize + 1]{};
			for (unsigned short i{}; i < numSize; ++i)
				temp[i + 1] = num[i];
			delete[] num;
			num = temp;
			++numSize;

			if (digitPosition != divisibleMantissaSize)
				num[0] = divisibleMantissa[divisibleMantissaSize - digitPosition - 1];

			unsigned short i = 0;
			--degree[i];
			while (i < _Constants.MaxDegreeLength && degree[i] < 0)
			{
				degree[i] = _Constants.Base - 1;
				++i;
				if (i < _Constants.MaxDegreeLength)
					--degree[i];
			}

			++digitPosition;
		}

		unsigned short counter = _Constants.MaxMantissaLength;
		int* result{};
		unsigned short resultSize = 0;

		bool numIsZero = false;
		while (!numIsZero && counter > 0)
		{
			bool isNumLess = false;
			if (numSize < divisorMantissaSize)
				isNumLess = true;
			else if (numSize == divisorMantissaSize)
				for (int i = divisorMantissaSize - 1; i >= 0; --i)
					if (num[i] < number._mantissa[i])
					{
						isNumLess = true;
						break;
					}
					else if (num[i] > number._mantissa[i])
						break;


			int* temp = new int[resultSize + 1]{};
			for (unsigned short i{}; i < resultSize; ++i)
				temp[i + 1] = result[i];
			delete[] result;
			result = temp;
			++resultSize;

			if (!isNumLess)
			{
				unsigned short k = 1;

				bool kIsFound = false;
				while (!kIsFound)
				{
					int* subtracted = new int[numSize] {};

					unsigned short r = 0;
					for (unsigned short i{}; i < divisorMantissaSize; ++i)
					{
						subtracted[i] = (number._mantissa[i] * k + r) % _Constants.Base;
						r = (number._mantissa[i] * k + r) / _Constants.Base;
					}
					if (numSize > divisorMantissaSize)
						subtracted[numSize - 1] = r;

					int* difference = new int[numSize] {};
					r = 0;
					for (unsigned short i{}; i < numSize; ++i)
					{
						difference[i] = num[i] - subtracted[i] - r;

						if (difference[i] < 0)
						{
							r = 1;
							difference[i] += _Constants.Base;
						}
						else
							r = 0;
					}

					delete[] subtracted;

					unsigned short differenceSize = numSize;
					for (int i = numSize - 1; i >= 0; --i)
						if (difference[i] != 0)
							break;
						else
							--differenceSize;

					if (differenceSize > divisorMantissaSize)
						++k;
					else if (differenceSize < divisorMantissaSize)
						kIsFound = true;
					else
					{
						bool isEqual = true;
						for (int i = divisorMantissaSize - 1; i >= 0; --i)
							if (difference[i] > number._mantissa[i])
							{
								++k;
								isEqual = false;
								break;
							}
							else if (difference[i] < number._mantissa[i])
							{
								kIsFound = true;
								isEqual = false;
								break;
							}
						if (isEqual)
							++k;
					}

					if (kIsFound)
					{
						delete[] num;
						num = new int[differenceSize] {};
						for (unsigned short i{}; i < differenceSize; ++i)
							num[i] = difference[i];
						numSize = differenceSize;
					}

					delete[] difference;
				}

				result[0] = k;
			}

			temp = new int[numSize + 1]{};
			for (unsigned short i{}; i < numSize; ++i)
				temp[i + 1] = num[i];
			delete[] num;
			num = temp;
			++numSize;

			if (digitPosition < divisibleMantissaSize)
			{
				num[0] = divisibleMantissa[divisibleMantissaSize - digitPosition - 1];
				++digitPosition;
			}

			--counter;

			numIsZero = true;
			for (unsigned short i{}; i < numSize; ++i)
				if (num[i] != 0)
				{
					numIsZero = false;
					break;
				}
		}

		Real* resultReal = new Real();

		resultReal->_sign = _sign && !number._sign || !_sign && number._sign;

		for (unsigned short i{}; i < resultSize; ++i)
			resultReal->_mantissa[i] = result[i];

		delete[] resultReal->_degree;
		resultReal->_degree = degree;
		delete[] result;
		delete[] num;
		delete[] divisibleMantissa;

		return resultReal;
	}

	void Real::IncDegree()
	{
		unsigned short i = 0;
		++_degree[i];
		while (i < _Constants.MaxDegreeLength && _degree[i] == _Constants.Base)
		{
			_degree[i] = 0;
			++i;
			if (i < _Constants.MaxDegreeLength)
				++_degree[i];
		}
	}

	void Real::DecDegree()
	{
		unsigned short i = 0;
		--_degree[i];
		while (i < _Constants.MaxDegreeLength && _degree[i] < 0)
		{
			_degree[i] = _Constants.Base - 1;
			++i;
			if (i < _Constants.MaxDegreeLength)
				--_degree[i];
		}
	}

	void Real::DecreaseDegree(int* value, unsigned short size)
	{
		unsigned short r = 0;
		for (unsigned short i{}; i < size; ++i)
		{
			_degree[i] -= r;

			_degree[i] -= value[i];

			if (_degree[i] < 0)
			{
				_degree[i] += _Constants.Base;
				r = 1;
			}
			else
				r = 0;
		}

		if (size < _Constants.MaxDegreeLength)
			_degree[size] -= r;
	}

	void Real::IncreaseDegree(int* value, unsigned short size)
	{
		unsigned short r = 0;
		for (unsigned short i{}; i < size; ++i)
		{
			_degree[i] += r;

			_degree[i] += value[i];

			if (_degree[i] >= _Constants.Base)
			{
				_degree[i] -= _Constants.Base;
				r = 1;
			}
			else
				r = 0;
		}

		if (size < _Constants.MaxDegreeLength)
			_degree[size] += r;
	}

	short Real::CompareDegree(int* value, unsigned short size)
	{
		if (size > _Constants.MaxDegreeLength)
			return 1;
		else if (size < _Constants.MaxDegreeLength)
			return -1;
		else
		{
			for (int i = _Constants.MaxDegreeLength - 1; i >= 0; --i)
			{
				if (value[i] > _degree[i])
					return 1;
				else if (value[i] < _degree[i])
					return -1;
			}
		}

		return 0;
	}

	int* Real::CopyDegree()
	{
		int* temp = new int[_Constants.MaxDegreeLength] {};
		for (unsigned short i{}; i < _Constants.MaxDegreeLength; ++i)
			temp[i] = _degree[i];
		return temp;
	}

	DivisionByZeroException::DivisionByZeroException(std::string error) : _error(error) {}
	std::string DivisionByZeroException::GetError() { return _error; }
}