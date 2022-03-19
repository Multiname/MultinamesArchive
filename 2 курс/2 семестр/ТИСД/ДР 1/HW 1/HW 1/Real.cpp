#include "Real.h"

#include <iostream>

namespace Real
{
	Real::Real() : _sign(false), _mantissa(new int[_MaxMantissaLength] {}),
		_degree(new int[_MaxDegreeLength] {})
	{
		_degreeShift = new int[_MaxDegreeLength] {};
		for (unsigned short i{}; i < _MaxDegreeLength - 1; ++i)
			_degreeShift[i] = _Base - 1;
		_degreeShift[_MaxDegreeLength - 1] = (_Base - 1) / 2;
	}

	Real::Real(std::string number)
	{
		_mantissa = new int[_MaxMantissaLength] {};
		_degree = new int[_MaxDegreeLength] {};
		_degreeShift = new int[_MaxDegreeLength] {};
		for (unsigned short i{}; i < _MaxDegreeLength - 1; ++i)
		{
			_degree[i] = _Base - 1;
			_degreeShift[i] = _Base - 1;
		}
		_degreeShift[_MaxDegreeLength - 1] = (_Base - 1) / 2;
		_degree[_MaxDegreeLength - 1] = (_Base - 1) / 2;

		unsigned short* temp = new unsigned short[_MaxMantissaLength] {};
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
		_degreeShift = new int [_MaxDegreeLength] {};
		_degree = new int[_MaxDegreeLength] {};
		_mantissa = new int[_MaxMantissaLength] {};

		for (unsigned short i{}; i < _MaxDegreeLength; ++i)
		{
			_degreeShift[i] = real._degreeShift[i];
			_degree[i] = real._degree[i];
		}
		for (unsigned short i{}; i < _MaxMantissaLength; ++i)
			_mantissa[i] = real._mantissa[i];
	}

	Real::~Real()
	{
		delete[] _degreeShift;
		delete[] _mantissa;
		delete[] _degree;
	}

	std::string Real::ToString()
	{
		std::string number = "";
		if (_sign)
			number += '-';

		int pos = -1;
		for (int i = _MaxMantissaLength - 1; i >= 0; --i)
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

		if (CompareDegree(_degreeShift, _MaxDegreeLength) == 1)
		{
			number += "-";

			_degree = _degreeShift;
			_degreeShift = CopyDegree();
			DecreaseDegree(temp, _MaxDegreeLength);
			DecDegree();

			int i = _MaxDegreeLength - 1;
			while (_degree[i] == 0)
				--i;
			for (; i >= 0; --i)
				number += (_degree[i] + '0');
		}
		else if (CompareDegree(_degreeShift, _MaxDegreeLength) == -1)
		{
			DecreaseDegree(_degreeShift, _MaxDegreeLength);

			int i = _MaxDegreeLength - 1;
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

	Real* Real::MultiplyByInt(int number)
	{
		Real* result = new Real(*this);
		if (number < 0)
			result->_sign = true;
		else
			result->_sign = false;

		number = abs(number);

		unsigned short startSize = _MaxMantissaLength;
		for (int i = _MaxMantissaLength - 1; i >= 0; --i)
		{
			if (_mantissa[i] != 0)
				break;
			--startSize;
		}

		unsigned short r = 0;
		for (unsigned short i{}; i < _MaxMantissaLength; ++i)
		{
			result->_mantissa[i] = (_mantissa[i] * number + r) % _Base;
			r = (_mantissa[i] * number + r) / _Base;
		}

		unsigned short endSize = _MaxMantissaLength;
		for (int i = _MaxMantissaLength - 1; i >= 0; --i)
		{
			if (result->_mantissa[i] != 0)
				break;
			--endSize;
		}

		result->IncreaseDegreeByUint(endSize - startSize);

		unsigned short shift = 0;
		for (; shift < _MaxMantissaLength; ++shift)
			if (result->_mantissa[shift] != 0)
				break;
		for (unsigned short i{}; i < _MaxMantissaLength - shift; ++i)
			result->_mantissa[i] = result->_mantissa[i + shift];
		for (unsigned short i = _MaxMantissaLength - shift; i < _MaxMantissaLength; ++i)
			result->_mantissa[i] = 0;

		return result;
	}

	short Real::CompareAbs(Real number)
	{
		if (CompareDegree(number._degree, _MaxDegreeLength) != 0)
			return CompareDegree(number._degree, _MaxDegreeLength);
		for (int i = _MaxMantissaLength - 1; i >= 0; --i)
			if (number._mantissa[i] > _mantissa[i])
				return 1;
			else if (number._mantissa[i] < _mantissa[i])
				return -1;
		return 0;
	}

	Real* Real::SubtractLessPlus(Real number)
	{
		int* temp = CopyDegree();

		DecreaseDegree(number._degree, _MaxDegreeLength);
		unsigned short degreeDifference = 0;
		for (unsigned short i{}; i < _MaxDegreeLength; ++i)
			degreeDifference += _degree[i] * pow(_Base, i);

		delete[] _degree;
		_degree = temp;

		unsigned short reducedMantissaSize = _MaxMantissaLength;
		for (int i = _MaxMantissaLength - 1; i >= 0; --i)
		{
			if (_mantissa[i] != 0)
				break;
			--reducedMantissaSize;
		}

		unsigned short subtractedMantissaSize = _MaxMantissaLength;
		for (int i = _MaxMantissaLength - 1; i >= 0; --i)
		{
			if (number._mantissa[i] != 0)
				break;
			--subtractedMantissaSize;
		}

		int expansion = subtractedMantissaSize - reducedMantissaSize + degreeDifference;
		if (expansion > 0)
		{
			unsigned short size = _MaxMantissaLength + expansion;
			int* reducedMantissa = new int[size] {};
			int* subtractedMantissa = new int[size] {};

			for (unsigned short i{}; i < _MaxMantissaLength; ++i)
			{
				reducedMantissa[i + expansion] = _mantissa[i];
				subtractedMantissa[i] = number._mantissa[i];
			}

			unsigned short r = 0;
			for (unsigned short i{}; i < size; ++i)
			{
				reducedMantissa[i] -= subtractedMantissa[i];
				reducedMantissa[i] -= r;

				if (reducedMantissa[i] < 0)
				{
					r = 1;
					reducedMantissa[i] += _Base;
				}
				else
					r = 0;
			}

			unsigned short startPointPosition = reducedMantissaSize + expansion - 1;
			int endPointPosition = size - 1;
			for (; endPointPosition >= 0; --endPointPosition)
				if (reducedMantissa[endPointPosition] != 0)
					break;
			if (endPointPosition == -1)
				return new Real();
			unsigned short degreeShift = startPointPosition - endPointPosition;

			unsigned short mantissaShift = 0;
			for (; mantissaShift < size; ++mantissaShift)
				if (reducedMantissa[mantissaShift] != 0)
					break;

			Real* result = new Real();
			if (endPointPosition - mantissaShift + 1 > _MaxMantissaLength)
				for (unsigned short i{}; i < _MaxMantissaLength; ++i)
					result->_mantissa[_MaxMantissaLength - i - 1] = reducedMantissa[endPointPosition - i];
			else
				for (unsigned short i{}; i < endPointPosition - mantissaShift + 1; ++i)
					result->_mantissa[i] = reducedMantissa[i + mantissaShift];
			
			delete[] result->_degree;
			result->_degree = CopyDegree();
			result->DecreaseDegreeByUint(degreeShift);

			return result;
		}
		else if (expansion < 0)
		{
			expansion *= -1;
			unsigned short size = _MaxMantissaLength + expansion;
			int* reducedMantissa = new int[size] {};
			int* subtractedMantissa = new int[size] {};

			for (unsigned short i{}; i < _MaxMantissaLength; ++i)
			{
				reducedMantissa[i] = _mantissa[i];
				subtractedMantissa[i + expansion] = number._mantissa[i];
			}

			unsigned short r = 0;
			for (unsigned short i{}; i < size; ++i)
			{
				reducedMantissa[i] -= subtractedMantissa[i];
				reducedMantissa[i] -= r;

				if (reducedMantissa[i] < 0)
				{
					r = 1;
					reducedMantissa[i] += _Base;
				}
				else
					r = 0;
			}

			unsigned short startPointPosition = reducedMantissaSize - 1;
			int endPointPosition = size - 1;
			for (; endPointPosition >= 0; --endPointPosition)
				if (reducedMantissa[endPointPosition] != 0)
					break;
			if (endPointPosition == -1)
				return new Real();
			unsigned short degreeShift = startPointPosition - endPointPosition;

			unsigned short mantissaShift = 0;
			for (; mantissaShift < size; ++mantissaShift)
				if (reducedMantissa[mantissaShift] != 0)
					break;

			Real* result = new Real();
			if (endPointPosition - mantissaShift + 1 > _MaxMantissaLength)
				for (unsigned short i{}; i < _MaxMantissaLength; ++i)
					result->_mantissa[_MaxMantissaLength - i - 1] = reducedMantissa[endPointPosition - i];
			else
				for (unsigned short i{}; i < endPointPosition - mantissaShift + 1; ++i)
					result->_mantissa[i] = reducedMantissa[i + mantissaShift];

			delete[] result->_degree;
			result->_degree = CopyDegree();
			result->DecreaseDegreeByUint(degreeShift);

			return result;
		}
		else
		{
			int* reducedMantissa = new int[_MaxMantissaLength] {};

			for (unsigned short i{}; i < _MaxMantissaLength; ++i)
				reducedMantissa[i] = _mantissa[i];

			unsigned short r = 0;
			for (unsigned short i{}; i < _MaxMantissaLength; ++i)
			{
				reducedMantissa[i] -= number._mantissa[i];
				reducedMantissa[i] -= r;

				if (reducedMantissa[i] < 0)
				{
					r = 1;
					reducedMantissa[i] += _Base;
				}
				else
					r = 0;
			}

			unsigned short startPointPosition = reducedMantissaSize - 1;
			int endPointPosition = _MaxMantissaLength - 1;
			for (; endPointPosition >= 0; --endPointPosition)
				if (reducedMantissa[endPointPosition] != 0)
					break;
			if (endPointPosition == -1)
				return new Real();
			unsigned short degreeShift = startPointPosition - endPointPosition;

			unsigned short mantissaShift = 0;
			for (; mantissaShift < _MaxMantissaLength; ++mantissaShift)
				if (reducedMantissa[mantissaShift] != 0)
					break;

			Real* result = new Real();
			for (unsigned short i{}; i < endPointPosition - mantissaShift + 1; ++i)
				result->_mantissa[i] = reducedMantissa[i + mantissaShift];

			delete[] result->_degree;
			result->_degree = CopyDegree();
			result->DecreaseDegreeByUint(degreeShift);

			return result;
		}
	}

	Real* Real::Divide(Real number)
	{
		int* degree{};
		if (CompareDegree(number._degree, _MaxDegreeLength) == -1)
		{
			int* temp = CopyDegree();

			DecreaseDegree(number._degree, _MaxDegreeLength);
			IncreaseDegree(_degreeShift, _MaxDegreeLength);
			degree = CopyDegree();

			_degree = temp;
		}
		else if (CompareDegree(number._degree, _MaxDegreeLength) == 1)
		{
			number.DecreaseDegree(_degree, _MaxDegreeLength);
			number.IncreaseDegree(_degreeShift, _MaxDegreeLength);
			degree = number.CopyDegree();
		}
		else
		{
			degree = new int[_MaxDegreeLength] {};
			for (unsigned short i{}; i < _MaxDegreeLength; ++i)
				degree[i] = _degreeShift[i];
		}

		unsigned short divisibleMantissaSize = _MaxMantissaLength;
		for (int i = _MaxMantissaLength - 1; i >= 0; --i)
			if (_mantissa[i] != 0)
				break;
			else
				--divisibleMantissaSize;

		unsigned short divisorMantissaSize = _MaxMantissaLength;
		for (int i = _MaxMantissaLength - 1; i >= 0; --i)
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
			while (i < _MaxDegreeLength && degree[i] < 0)
			{
				degree[i] = _Base - 1;
				++i;
				if (i < _MaxDegreeLength)
					--degree[i];
			}

			++digitPosition;
		}

		unsigned short counter = _MaxMantissaLength;
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
						subtracted[i] = (number._mantissa[i] * k + r) % _Base;
						r = (number._mantissa[i] * k + r) / _Base;
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
							difference[i] += _Base;
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

		return resultReal;
	}

	void Real::IncDegree()
	{
		unsigned short i = 0;
		++_degree[i];
		while (i < _MaxDegreeLength && _degree[i] == _Base)
		{
			_degree[i] = 0;
			++i;
			if (i < _MaxDegreeLength)
				++_degree[i];
		}
	}

	void Real::DecDegree()
	{
		unsigned short i = 0;
		--_degree[i];
		while (i < _MaxDegreeLength && _degree[i] < 0)
		{
			_degree[i] = _Base - 1;
			++i;
			if (i < _MaxDegreeLength)
				--_degree[i];
		}
	}

	void Real::IncreaseDegreeByUint(unsigned short number)
	{
		unsigned short r = 0;
		for (unsigned short i{}; i < _MaxDegreeLength; ++i)
		{
			_degree[i] += (number / (int)pow(_Base, i)) % _Base + r;
			r = _degree[i] / _Base;
			_degree[i] %= _Base;
		}
	}

	void Real::DecreaseDegreeByUint(unsigned short number)
	{
		unsigned short r = 0;
		for (unsigned short i{}; i < _MaxDegreeLength; ++i)
		{
			_degree[i] -= (number / (int)pow(_Base, i)) % _Base + r;
			if (_degree[i] < 0)
			{
				r = 1;
				_degree += _Base;
			}
			else
				r = 0;
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
				_degree[i] += _Base;
				r = 1;
			}
			else
				r = 0;
		}

		if (size < _MaxDegreeLength)
			_degree[size] -= r;
	}

	void Real::IncreaseDegree(int* value, unsigned short size)
	{
		unsigned short r = 0;
		for (unsigned short i{}; i < size; ++i)
		{
			_degree[i] += r;

			_degree[i] += value[i];

			if (_degree[i] >= _Base)
			{
				_degree[i] -= _Base;
				r = 1;
			}
			else
				r = 0;
		}

		if (size < _MaxDegreeLength)
			_degree[size] += r;
	}

	short Real::CompareDegree(int* value, unsigned short size)
	{
		if (size > _MaxDegreeLength)
			return 1;
		else if (size < _MaxDegreeLength)
			return -1;
		else
		{
			for (int i = _MaxDegreeLength - 1; i >= 0; --i)
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
		int* temp = new int[_MaxDegreeLength] {};
		for (unsigned short i{}; i < _MaxDegreeLength; ++i)
			temp[i] = _degree[i];
		return temp;
	}
}