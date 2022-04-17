#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <string>

namespace DTAS
{
	class IncorrectWeightException
	{
	public:
		IncorrectWeightException(std::string error) : _error(error) {}
		std::string GetError() { return _error; }

	private:
		std::string _error{};
	};

	template <typename T>
	class Graph
	{
	public:
		Graph() : _weights(nullptr), _size(), _elements(), _outputFile("Output.txt") {}

		Graph(std::string inputFile) : Graph(inputFile, "Output.txt") {}

		Graph(std::string inputFile, std::string outputFile) : _outputFile(outputFile)
		{
			std::ifstream file(inputFile);
			file >> _size;

			for (int i{}; i < _size; ++i)
			{
				T element{};
				file >> element;
				_elements.push_back(element);
			}

			_weights = new int** [_size] {};
			for (int i{}; i < _size; ++i)
			{
				_weights[i] = new int* [_size] {};
				for (int j{}; j < _size; ++j)
				{
					std::string weight{};
					file >> weight;
					if (weight == "-")
						_weights[i][j] = nullptr;
					else if (std::find_if(weight.begin(), weight.end(), [](char c) { return !std::isdigit(c); }) != weight.end())
						throw IncorrectWeightException("Incorrect weight");
					else
						_weights[i][j] = new int(std::stoi(weight));
				}
			}

			file.close();
		}

		~Graph()
		{
			for (int i{}; i < _size; ++i)
			{
				for (int j{}; j < _size; ++j)
					if (_weights[i][j] != nullptr)
						delete _weights[i][j];
				delete[] _weights[i];
			}
			delete[] _weights;
		}

		bool IsEmpty() { return _weights == nullptr; }

		void Clear()
		{
			if (!IsEmpty())
			{
				for (int i{}; i < _size; ++i)
				{
					for (int j{}; j < _size; ++j)
						if (_weights[i][j] != nullptr)
							delete _weights[i][j];
					delete[] _weights[i];
				}
				delete[] _weights;

				_weights = nullptr;
				_elements.clear();
				_size = 0;
			}
		}

		void Print(int width)
		{
			if (IsEmpty())
				std::cout << "Graph is empty\n";
			else
			{
				std::cout << std::setw(width) << " ";
				for (int i{}; i < _size; ++i)
					std::cout << std::setw(width) << _elements[i];
				std::cout << "\n";

				for (int i{}; i < _size; ++i)
				{
					std::cout << std::setw(width) << _elements[i];
					for (int j{}; j < _size; ++j)
						if (_weights[i][j] != nullptr)
							std::cout << std::setw(width) << *_weights[i][j];
						else
							std::cout << std::setw(width) << "-";
					std::cout << "\n";
				}
			}
		}

		void Add(T element)
		{
			int*** temp = new int** [_size + 1]{};
			for (int j{}; j < _size + 1; ++j)
				temp[j] = new int* [_size + 1]{};

			for (int j{}; j < _size; ++j)
				for (int k{}; k < _size; ++k)
					if (_weights[j][k] != nullptr)
						temp[j][k] = new int(*_weights[j][k]);

			for (int i{}; i < _size; ++i)
			{
				for (int j{}; j < _size; ++j)
					if (_weights[i][j] != nullptr)
						delete _weights[i][j];
				delete[] _weights[i];
			}
			delete[] _weights;

			_weights = temp;
			_elements.push_back(element);
			++_size;
		}

		void Connect(T source, T destination, std::string weight)
		{
			int s;
			for (s = 0; s < _size; ++s)
				if (_elements[s] == source)
					break;

			int d;
			if (source == destination)
				d = s;
			else
			{
				for (d = 0; d < _size; ++d)
					if (_elements[d] == destination)
						break;
			}

			if (s < _size && d < _size)
			{
				delete _weights[s][d];
				if (weight == "-")
					_weights[s][d] = nullptr;
				else if (std::find_if(weight.begin(), weight.end(), [](char c) { return !std::isdigit(c); }) != weight.end())
					throw IncorrectWeightException("Incorrect weight");
				else
					_weights[s][d] = new int(std::stoi(weight));
			}
		}

		void Remove(T element)
		{
			int i;
			for (i = 0; i < _size; ++i)
				if (_elements[i] == element)
					break;

			if (i < _size)
			{
				int*** temp = nullptr;
				if (_size > 1)
				{
					temp = new int** [_size - 1]{};
					for (int j{}; j < _size - 1; ++j)
						temp[j] = new int* [_size - 1]{};

					for (int j{}; j < i; ++j)
					{
						for (int k{}; k < i; ++k)
							if (_weights[j][k] != nullptr)
								temp[j][k] = new int(*_weights[j][k]);
						for (int k = i + 1; k < _size; ++k)
							if (_weights[j][k] != nullptr)
								temp[j][k - 1] = new int(*_weights[j][k]);
					}
					for (int j = i + 1; j < _size; ++j)
					{
						for (int k{}; k < i; ++k)
							if (_weights[j][k] != nullptr)
								temp[j - 1][k] = new int(*_weights[j][k]);
						for (int k = i + 1; k < _size; ++k)
							if (_weights[j][k] != nullptr)
								temp[j - 1][k - 1] = new int(*_weights[j][k]);
					}
				}

				for (int j{}; j < _size; ++j)
				{
					for (int k{}; k < _size; ++k)
						if (_weights[j][k] != nullptr)
							delete _weights[j][k];
					delete[] _weights[j];
				}
				delete[] _weights;


				_weights = temp;
				_elements.erase(_elements.begin() + i);
				--_size;
			}
		}

		void DFS(T start)
		{
			if (IsEmpty())
				std::cout << "Graph is empty\n";
			else
			{
				int i;
				for (i = 0; i < _size; ++i)
					if (_elements[i] == start)
						break;

				if (i < _size)
				{
					bool* visited = new bool[_size] {};
					DFS(i, visited);
					delete[] visited;
				}
			}
		}

		void BFS(T start)
		{
			if (IsEmpty())
				std::cout << "Graph is empty\n";
			else
			{
				int index;
				for (index = 0; index < _size; ++index)
					if (_elements[index] == start)
						break;

				if (index < _size)
				{
					bool* visited = new bool[_size] {};
					std::queue<int> waiting{};
					waiting.push(index);
					visited[index] = true;

					while (!waiting.empty())
					{
						index = waiting.front();
						waiting.pop();
						std::cout << _elements[index] << " ";

						std::vector<int> unsorted{};
						for (int i{}; i < _size; ++i)
							if ((_weights[index][i] != nullptr) && (!visited[i]))
							{
								unsorted.push_back(i);
								visited[i] = true;
							}

						std::sort(unsorted.begin(), unsorted.end(), [&](int a, int b) { return *_weights[index][a] < *_weights[index][b]; });
						for (int i{}; i < unsorted.size(); ++i)
							waiting.push(unsorted[i]);
					}

					delete[] visited;
				}
			}
		}

		void PrintMaxDistances(int width)
		{
			std::ofstream file(_outputFile);

			if (IsEmpty())
			{
				std::cout << "Graph is empty\n";
				file << "Graph is empty";
			}
			else
			{
				int*** maxDistances = new int** [_size] {};
				for (int i{}; i < _size; ++i)
					maxDistances[i] = new int* [_size] {};

				for (int i{}; i < _size; ++i)
					for (int j{}; j < _size; ++j)
					{
						std::vector<Pair> passed{};
						maxDistances[i][j] = FindMaxDistance(i, j, passed);
					}

				std::cout << std::setw(width) << " ";
				file << std::setw(width) << " ";
				for (int i{}; i < _size; ++i)
				{
					std::cout << std::setw(width) << _elements[i];
					file << std::setw(width) << _elements[i];
				}
				std::cout << "\n";
				file << "\n";

				for (int i{}; i < _size; ++i)
				{
					std::cout << std::setw(width) << _elements[i];
					file << std::setw(width) << _elements[i];
					for (int j{}; j < _size; ++j)
						if (maxDistances[i][j] != nullptr)
						{
							std::cout << std::setw(width) << *maxDistances[i][j];
							file << std::setw(width) << *maxDistances[i][j];
						}
						else
						{
							std::cout << std::setw(width) << "-";
							file << std::setw(width) << "-";
						}
					std::cout << "\n";
					file << "\n";
				}

				for (int i{}; i < _size; ++i)
				{
					for (int j{}; j < _size; ++j)
						if (maxDistances[i][j] != nullptr)
							delete maxDistances[i][j];
					delete[] maxDistances[i];
				}
				delete[] maxDistances;
			}

			file.close();
		}

	private:
		void DFS(int index, bool* visited)
		{
			std::cout << _elements[index] << " ";
			visited[index] = true;
			for (int i{}; i < _size; ++i)
				if ((_weights[index][i] != nullptr) && (!visited[i]))
					DFS(i, visited);
		}

		struct Pair
		{
			int i{};
			int j{};
		};

		int* FindMaxDistance(int source, int destination, std::vector<Pair> passed)
		{
			if (source == destination)
				return new int(0);

			int* maxDistance = nullptr;
			for (int i{}; i < _size; ++i)
			{
				Pair pair{ source, i };
				if (_weights[source][i] != nullptr && std::find_if(passed.begin(), passed.end(),
					[&](Pair a) { return a.i == pair.i && a.j == pair.j || a.i == pair.j && a.j == pair.i; }) == passed.end())
				{
					passed.push_back(pair);
					int* distance = FindMaxDistance(i, destination, passed);
					passed.pop_back();
					if (distance != nullptr)
					{
						*distance += *_weights[source][i];
						if (maxDistance == nullptr)
							maxDistance = distance;
						else if (*distance > *maxDistance)
						{
							delete maxDistance;
							maxDistance = distance;
						}
					}
				}
			}

			return maxDistance;
		}

		int*** _weights{};
		uint16_t _size{};
		std::vector<T> _elements{};
		std::string _outputFile{};
	};
}