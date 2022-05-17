#include "Knuth.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace LW_4
{
	Knuth::Knuth(): _saveFile("Output.txt"),
		_an{}, _i{}, _j{}, _nr{}, _nc{}, _jr{}, _jc{},
		_numberOfRows{}, _numberOfColumns{} {}

	Knuth::Knuth(std::string inputFile, std::string saveFile): _saveFile(saveFile)
	{
		std::ifstream file(inputFile);
		std::string line{};
		uint16_t i = 1;
		_numberOfColumns = 0;
		while (std::getline(file, line))
		{
			uint16_t j = 1;
			bool rowStartIsFounded = false;
			std::string number{};
			std::istringstream stream(line);
			while (stream >> number)
			{
				if (number != "0")
				{
					_an.push_back(std::stoi(number));
					_i.push_back(i);
					_j.push_back(j);

					if (j > _numberOfColumns)
						_numberOfColumns = j;

					if (!rowStartIsFounded)
					{
						_jr.push_back(_i.size());
						rowStartIsFounded = true;
					}
				}
				++j;
			}
			++i;

			if (!rowStartIsFounded)
				_jr.push_back(0);
		}
		file.close();

		_numberOfRows = _jr.size();

		for (uint16_t k{}; k < _i.size() - 1; ++k)
		{
			if (_i[k] == _i[k + 1])
				_nr.push_back(k + 2);
			else
				_nr.push_back(0);
		}
		_nr.push_back(0);

		for (uint16_t k{}; k < _j.size() - 1; ++k)
		{
			uint16_t l;
			for (l = k + 1; l < _j.size(); ++l)
				if (_j[k] == _j[l])
				{
					_nc.push_back(l + 1);
					break;
				}
			if (l == _j.size())
				_nc.push_back(0);
		}
		_nc.push_back(0);

		for (uint16_t k{}; k < _numberOfColumns; ++k)
		{
			uint16_t l;
			for (l = 0; l < _j.size(); ++l)
			{
				if (_j[l] == k + 1)
				{
					_jc.push_back(l + 1);
					break;
				}
			}
			if (l == _j.size())
				_jc.push_back(0);
		}
	}

	void Knuth::Restore()
	{
		int** matrix = new int* [_numberOfRows] {};
		for (uint16_t i{}; i < _numberOfRows; ++i)
			matrix[i] = new int[_numberOfColumns] {};

		for (uint16_t i{}; i < _an.size(); ++i)
			matrix[_i[i] - 1][_j[i] - 1] = _an[i];

		std::cout << "    ";
		for (uint16_t j{}; j < _numberOfColumns; ++j)
			std::cout << j + 1 << " ";
		std::cout << "\n\n";
		for (uint16_t i{}; i < _numberOfRows; ++i)
		{
			std::cout << i + 1 << "   ";
			for (uint16_t j{}; j < _numberOfColumns; ++j)
				std::cout << matrix[i][j] << " ";
			std::cout << "\n";
		}

		for (uint16_t i{}; i < _numberOfRows; ++i)
			delete[] matrix[i];
		delete[] matrix;
	}

	void Knuth::ShowNumberAtPosition(uint16_t i, uint16_t j)
	{
		uint16_t k;
		for (k = 0; k < _an.size(); ++k)
			if (_i[k] == i && _j[k] == j)
			{
				std::cout << _an[k];
				return;
			}

		std::cout << 0;
	}

	void Knuth::Print()
	{
		std::cout << "     ";
		for (uint16_t i{}; i < _an.size(); ++i)
			std::cout << i + 1 << " ";
		std::cout << "\n";

		std::cout << "AN = ";
		for (uint16_t i{}; i < _an.size(); ++i)
			std::cout << _an[i] << " ";
		std::cout << "\n";

		std::cout << "I  = ";
		for (uint16_t i{}; i < _i.size(); ++i)
			std::cout << _i[i] << " ";
		std::cout << "\n";

		std::cout << "J  = ";
		for (uint16_t i{}; i < _j.size(); ++i)
			std::cout << _j[i] << " ";
		std::cout << "\n";

		std::cout << "NR = ";
		for (uint16_t i{}; i < _nr.size(); ++i)
			std::cout << _nr[i] << " ";
		std::cout << "\n";

		std::cout << "NC = ";
		for (uint16_t i{}; i < _nc.size(); ++i)
			std::cout << _nc[i] << " ";
		std::cout << "\n";

		std::cout << "JR = ";
		for (uint16_t i{}; i < _jr.size(); ++i)
			std::cout << _jr[i] << " ";
		std::cout << "\n";

		std::cout << "JC = ";
		for (uint16_t i{}; i < _jc.size(); ++i)
			std::cout << _jc[i] << " ";
		std::cout << "\n";
	}

	void Knuth::ReplaceColumns(uint16_t firstColumn, uint16_t secondColumn)
	{
		if (firstColumn != secondColumn)
		{
			for (uint16_t i{}; i < _numberOfRows; ++i)
			{
				int firstIndex = 0;
				int secondIndex = 0;

				for (uint16_t j{}; j < _an.size(); ++j)
				{
					if (_i[j] == i + 1 && _j[j] == firstColumn)
						firstIndex = j + 1;
					if (_i[j] == i + 1 && _j[j] == secondColumn)
						secondIndex = j + 1;
				}

				if (firstIndex != 0 && secondIndex != 0)
				{
					int temp = _an[firstIndex - 1];
					_an[firstIndex - 1] = _an[secondIndex - 1];
					_an[secondIndex - 1] = temp;
				}
				else if (firstIndex != 0 && firstIndex < _an.size())
				{
					uint16_t analysedIndex = firstIndex + 1;
					while (_i[firstIndex - 1] == _i[analysedIndex - 1] &&
						_j[analysedIndex - 1] < secondColumn &&
						analysedIndex - 1 < _an.size())
					{
						int temp = _an[firstIndex - 1];
						_an[firstIndex - 1] = _an[analysedIndex - 1];
						_an[analysedIndex - 1] = temp;

						temp = _j[analysedIndex - 2];
						_j[analysedIndex - 2] = _j[analysedIndex - 1];
						_j[analysedIndex - 1] = temp;

						++analysedIndex;
					}

					_j[analysedIndex - 2] = secondColumn;
				}
				else if (secondIndex != 0 && secondIndex > 1)
				{
					int16_t analysedIndex = secondIndex - 1;
					while (_i[secondIndex - 1] == _i[analysedIndex - 1] &&
						_j[analysedIndex - 1] > firstColumn &&
						analysedIndex > 0)
					{
						int temp = _an[secondIndex - 1];
						_an[secondIndex - 1] = _an[analysedIndex - 1];
						_an[analysedIndex - 1] = temp;

						temp = _j[analysedIndex];
						_j[analysedIndex] = _j[analysedIndex - 1];
						_j[analysedIndex - 1] = temp;

						--analysedIndex;
					}

					_j[analysedIndex] = firstColumn;
				}
			}

			_nc.clear();
			for (uint16_t i{}; i < _j.size() - 1; ++i)
			{
				uint16_t j;
				for (j = i + 1; j < _j.size(); ++j)
					if (_j[i] == _j[j])
					{
						_nc.push_back(j + 1);
						break;
					}
				if (j == _j.size())
					_nc.push_back(0);
			}
			_nc.push_back(0);

			_jc.clear();
			for (uint16_t i{}; i < _numberOfColumns; ++i)
			{
				uint16_t j;
				for (j = 0; j < _j.size(); ++j)
				{
					if (_j[j] == i + 1)
					{
						_jc.push_back(j + 1);
						break;
					}
				}
				if (j == _j.size())
					_jc.push_back(0);
			}
		}

		Save();
	}

	void Knuth::Save()
	{
		std::ofstream file(_saveFile);
		file << "AN = ";
		for (uint16_t i{}; i < _an.size(); ++i)
			file << _an[i] << " ";
		file << "\n";

		file << "I  = ";
		for (uint16_t i{}; i < _i.size(); ++i)
			file << _i[i] << " ";
		file << "\n";

		file << "J  = ";
		for (uint16_t i{}; i < _j.size(); ++i)
			file << _j[i] << " ";
		file << "\n";

		file << "NR = ";
		for (uint16_t i{}; i < _nr.size(); ++i)
			file << _nr[i] << " ";
		file << "\n";

		file << "NC = ";
		for (uint16_t i{}; i < _nc.size(); ++i)
			file << _nc[i] << " ";
		file << "\n";

		file << "JR = ";
		for (uint16_t i{}; i < _jr.size(); ++i)
			file << _jr[i] << " ";
		file << "\n";

		file << "JC = ";
		for (uint16_t i{}; i < _jc.size(); ++i)
			file << _jc[i] << " ";
		file << "\n";
		file.close();
	}
}