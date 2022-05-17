#include "Graph.h"
#include <iostream>

DTAS::Graph<std::string> EdmondsKarp(DTAS::Graph<std::string> network,
	std::vector<uint16_t> s, std::vector<uint16_t> t);

int main()
{
	DTAS::Graph<std::string> graph("Input.txt");
	std::cout << "Network:\n";
	graph.Print(4);

	std::string input{};
	std::cout << "\nInput sources ('-' to stop):\n";
	std::vector<uint16_t> s{};
	while (true)
	{
		std::cout << ">>> ";
		std::cin >> input;
		if (input == "-")
			break;

		uint16_t index;
		for (index = 0; index < graph.GetSize(); ++index)
			if (graph.GetElement(index) == input)
				break;

		if (index >= graph.GetSize())
			continue;

		s.push_back(index);
	}

	std::cout << "\nInput sinks ('-' to stop):\n";
	std::vector<uint16_t> t{};
	while (true)
	{
		std::cout << ">>> ";
		std::cin >> input;
		if (input == "-")
			break;

		uint16_t index;
		for (index = 0; index < graph.GetSize(); ++index)
			if (graph.GetElement(index) == input)
				break;

		if (index >= graph.GetSize())
			continue;

		t.push_back(index);
	}

	DTAS::Graph<std::string> f = EdmondsKarp(graph, s, t);
	std::cout << "\nMax flow:\n";
	f.Print(4);

	return 0;
}

DTAS::Graph<std::string> EdmondsKarp(DTAS::Graph<std::string> network,
	std::vector<uint16_t> s, std::vector<uint16_t> t)
{
	int weight;

	std::vector<std::string> elements{};
	elements.push_back("S");
	for (uint16_t i{}; i < network.GetSize(); ++i)
		elements.push_back(network.GetElement(i));
	elements.push_back("T");

	DTAS::Graph<std::string> G(network.GetSize() + 2, elements);
	for (uint16_t i{}; i < network.GetSize(); ++i)
		for (uint16_t j{}; j < network.GetSize(); ++j)
			if (network.GetWeight(i, j, weight))
				G.SetWeight(i + 1, j + 1, new int(weight));
			else
				G.SetWeight(i + 1, j + 1, nullptr);

	for (uint16_t i{}; i < s.size(); ++i)
		G.SetWeight(0, s[i] + 1, new int(INT_MAX));
	for (uint16_t i{}; i < t.size(); ++i)
		G.SetWeight(t[i] + 1, G.GetSize() - 1, new int(INT_MAX));

	DTAS::Graph<std::string> f(G);
	for (uint16_t i{}; i < G.GetSize(); ++i)
		for (uint16_t j{}; j < G.GetSize(); ++j)
		{
			if (G.CheckConnection(i, j))
			{
				f.SetWeight(i, j, new int(0));
				f.SetWeight(j, i, new int(0));
			}
		}

	std::vector<uint16_t> p = G.FindShortestWay(0, G.GetSize() - 1);
	while (!p.empty())
	{
		int c = INT_MAX;
		for (uint16_t i{}; i < p.size() - 1; ++i)
		{
			G.GetWeight(p[i], p[i + 1], weight);
			if (c > weight)
				c = weight;
		}

		for (uint16_t i{}; i < p.size() - 1; ++i)
		{
			f.GetWeight(p[i], p[i + 1], weight);
			f.SetWeight(p[i], p[i + 1], new int(weight + c));
			f.SetWeight(p[i + 1], p[i], new int(-weight - c));
		}

		for (uint16_t i{}; i < p.size() - 1; ++i)
		{
			if (!G.GetWeight(p[i], p[i + 1], weight))
				weight = 0;

			if (weight - c == 0)
				G.SetWeight(p[i], p[i + 1], nullptr);
			else
				G.SetWeight(p[i], p[i + 1], new int(weight - c));

			if (!G.GetWeight(p[i + 1], p[i], weight))
				weight = 0;

			if (weight + c == 0)
				G.SetWeight(p[i + 1], p[i], nullptr);
			else
				G.SetWeight(p[i + 1], p[i], new int(weight + c));
		}

		p = G.FindShortestWay(0, G.GetSize() - 1);
	}

	DTAS::Graph<std::string> r(network);
	for (uint16_t i{}; i < network.GetSize(); ++i)
		for (uint16_t j{}; j < network.GetSize(); ++j)
			if (f.GetWeight(i + 1, j + 1, weight))
				r.SetWeight(i, j, new int(weight));
			else
				r.SetWeight(i, j, nullptr);

	return r;
}