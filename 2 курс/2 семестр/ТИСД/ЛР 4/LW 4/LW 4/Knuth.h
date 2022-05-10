#pragma once
#include <vector>
#include <string>

namespace LW_4
{
	class Knuth
	{
	public:
		Knuth(std::string inputFile, std::string saveFile = "Output.txt");

		void Print();
		void ReplaceColumns(uint16_t firstColumn, uint16_t secondColumn);

	private:
		void Save();

		std::string _saveFile{};

		std::vector<int> _an{};
		std::vector<uint16_t> _i{};
		std::vector<uint16_t> _j{};
		std::vector<uint16_t> _nr{};
		std::vector<uint16_t> _nc{};
		std::vector<uint16_t> _jr{};
		std::vector<uint16_t> _jc{};

		uint16_t _numberOfRows{};
		uint16_t _numberOfColumns{};
	};
}