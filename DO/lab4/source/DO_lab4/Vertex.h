#pragma once

#include <vector>
#include <utility>

struct Vertex
{
	int Index;
	std::vector<std::pair<int, double>> Connections;
};

