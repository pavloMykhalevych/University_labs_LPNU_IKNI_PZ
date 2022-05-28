#pragma once

#include <vector>
#include <utility>

#include "Connection.h"

struct Vertex
{
	int Index;
	std::vector<Connection> Connections;
};

