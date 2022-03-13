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
			if (number[i] == '0')
			{
				temp[t] = 0;

				if (isPointReached && !isNotZeroReached)
					DecDegree();
				else if (!isPointReached && isNotZeroReached)
					IncDegree();

				++t;
			}

			if (number[i] == '-')
				_sign = true;
			if (number[i] == '.')
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

		//unsigned short shift = degreeDifference - (reducedMantissaSize - subtractedMantissaSize);

		//Real* result = new Real(*this);
		//result->IncreaseDegreeByUint(degreeDifference);

		//for (unsigned short i = shift; i < _MaxMantissaLength; ++i)
		//	result->_mantissa[i] = _mantissa[i - shift];
		//for (unsigned short i{}; i < shift; ++i)
		//	result->_mantissa[i] = 0;

		//unsigned short r = 0;
		//for (unsigned short i{}; i < _MaxMantissaLength; ++i)
		//{
		//	result->_mantissa[i] -= number._mantissa[i];
		//	result->_mantissa[i] -= r;

		//	if (result->_mantissa[i] < 0)
		//	{
		//		r = 1;
		//		result->_mantissa[i] += _Base;
		//	}
		//	else
		//		r = 0;
		//}

		//unsigned short startPointPosition = reducedMantissaSize + shift - degreeDifference - 1;
		//int endPointPosition = _MaxMantissaLength - 1;
		//for (; endPointPosition >= 0; --endPointPosition)
		//	if (result->_mantissa[endPointPosition] != 0)
		//		break;

		//if (endPointPosition == -1)
		//	return new Real();

		//unsigned short degreeShift = endPointPosition - startPointPosition;

	}

	void Real::IncDegree()
	{
		unsigned short i = 0;
		++_degree[i];
		while (_degree[i] == _Base)
		{
			_degree[i] = 0;
			++i;
			++_degree[i];
		}
	}

	void Real::DecDegree()
	{
		unsigned short i = 0;
		--_degree[i];
		while (_degree[i] < 0)
		{
			_degree[i] = _Base - 1;
			++i;
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