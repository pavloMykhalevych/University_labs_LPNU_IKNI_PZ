#include "HomoriHu.h"

#include <json.h>

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

void HomoriHu::Start() {
	CreateProblem(false, "lab7_homori_24.json");
	BuildRoute();
}

void HomoriHu::CreateProblem(const bool fromConsole, std::string fileName) {
	if (fromConsole) {
		std::cout << "Enter number of peeks:";
		int peeksNumber;
		std::cin >> peeksNumber;
		m_costs.resize(peeksNumber, std::vector<double>(peeksNumber, 0));
		std::cout << "Enter costs:";
		for (int i = 0; i < peeksNumber; ++i) {
			for (int j = 0; j < peeksNumber; ++j) {
				std::cout << "c[" << i + 1 << "][" << j + 1 << "] = ";
				std::cin >> m_costs[i][j];
			}
		}
		std::cout << "Enter the start peek:";
		std::cin >> m_startPeek;
		std::cout << "Enter the end peek:";
		std::cin >> m_endPeek;
	}
	else {
		std::ifstream jsonFile(fileName);
		if (jsonFile.fail())
		{
			throw std::runtime_error("File was not found.\n");
		}
		nlohmann::json parsedJson = nlohmann::json::parse(jsonFile);
		const auto& parsedJsonCosts = parsedJson.at("Costs");
		const auto peeksCount = parsedJson.at("PeeksCount").get<int>();
		m_costs.resize(peeksCount, std::vector<double>(peeksCount, 0));

		for (int i = 0; i < peeksCount; ++i) {
			for (int j = 0; j < peeksCount; ++j) {
				m_costs[i][j] = parsedJsonCosts[i][j].get<double>();
			}
		}
		m_startPeek = parsedJson.at("StartPeek").get<int>();
		m_endPeek = parsedJson.at("EndPeek").get<int>();
	}
}

void HomoriHu::BuildRoute() {
	const int vertexCount = m_costs.size();
	double max = 0;
	int vertexIdx_1 = -1;
	m_step = 1;
	std::vector<std::vector<int>> vertexGroups;

	FindVertexWithMaxFlow(max, vertexIdx_1);

	if (vertexIdx_1 == -1) {
		throw std::runtime_error("Can't find start vertex");
	}

	m_usedVertices.push_back(vertexIdx_1);

	std::vector<int> group;
	group.push_back(vertexIdx_1);

	m_vertices.push_back(Vertex{ vertexIdx_1, {std::pair<int, double>(-1, FindFlowSum(group)) } });

	int startVertex = vertexIdx_1;

	vertexGroups.push_back(group);

	while (m_step < vertexCount - 1) {
		max = 0;
		auto vertexIdx = -1;
		if (startVertex != -1) {
			FindVertexFromStart(max, vertexIdx, startVertex);
		}
		else {
			FindVertexWithMaxFlow(max, vertexIdx);
		}
		m_usedVertices.push_back(vertexIdx);

		double min = std::numeric_limits<double>::max();

		int groupIdx = -1;

		for (int i = 0; i < vertexGroups.size(); ++i) {
			auto new_group = vertexGroups[i];
			if (!HasConnection(new_group, vertexIdx)) {
				continue;
			}

			new_group.push_back(vertexIdx);
			auto value = FindFlowSum(new_group);
			if (value < min) {
				min = value;
				groupIdx = i;
			}
		}

		std::vector<int> new_group(1, vertexIdx);
		auto value = FindFlowSum(new_group);
		if (value < min) {
			vertexGroups.push_back(new_group);
			m_vertices.push_back(Vertex{ vertexIdx, {std::pair<int, double>(-1, value) } });
		}
		else {
			vertexGroups[groupIdx].push_back(vertexIdx);
			for (int i = 0; i < m_vertices.size(); ++i) {
				if (std::find(vertexGroups[groupIdx].begin(), vertexGroups[groupIdx].end(), m_vertices[i].Index) == vertexGroups[groupIdx].end()) {
					continue;
				}
				for (auto& connection : m_vertices[i].Connections) {
					if (connection.first == -1) {
						connection.first = vertexIdx;
						break;
					}
				}
			}
			m_vertices.push_back(Vertex{ vertexIdx, {std::pair<int, double>(-1, min) } });
		}

		m_step++;
	}

	int unusedVertex = -1;
	for (int i = 0; i < vertexCount; ++i) {
		if (std::find(m_usedVertices.begin(), m_usedVertices.end(), i) != m_usedVertices.end()) {
			continue;
		}
		unusedVertex = i;
	}

	std::vector<std::pair<int, double>> connections;

	for (int i = 0; i < m_vertices.size(); ++i) {
		for (auto& connection : m_vertices[i].Connections) {
			if (connection.first == -1) {
				connection.first = unusedVertex;
				connections.push_back({ m_vertices[i].Index, connection.second });
				break;
			}
		}
	}
	m_vertices.push_back(Vertex{ unusedVertex, connections });

}

bool HomoriHu::HasConnection(const std::vector<int>& group, int vertex) {
	for (int i = 0; i < group.size(); ++i) {
		if (m_costs[group[i]][vertex] != -1) {
			return true;
		}
	}
	return false;
}

void HomoriHu::FindVertexWithMaxFlow(double& value, int& vertexidx) {
	const int vertexCount = m_costs.size();
	for (int i = 0; i < vertexCount; ++i) {
		if (std::find(m_usedVertices.begin(), m_usedVertices.end(), i) != m_usedVertices.end()) {
			continue;
		}
		for (int j = i + 1; j < vertexCount; ++j) {
			if (m_costs[i][j] > value) {
				value = m_costs[i][j];
				vertexidx = i;
			}
		}
	}
}

void HomoriHu::FindVertexFromStart(double& value, int& vertexidx, int& startVertex) {
	const int vertexCount = m_costs.size();
	for (int j = 0; j < vertexCount; ++j) {
		if (std::find(m_usedVertices.begin(), m_usedVertices.end(), j) != m_usedVertices.end()) {
			continue;
		}
		if (m_costs[startVertex][j] > value) {
			value = m_costs[startVertex][j];
			vertexidx = j;
		}
	}
	if (vertexidx == -1) {
		startVertex = -1;
		FindVertexWithMaxFlow(value, vertexidx);
	}
}

double HomoriHu::FindFlowSum(const std::vector<int>& group) {
	double result = 0.f;
	for (int i = 0; i < group.size(); ++i) {
		const int rowIdx = group[i];
		for (int j = 0; j < m_costs.size(); ++j) {
			if (std::find(group.begin(), group.end(), j) != group.end() || m_costs[rowIdx][j] == -1) {
				continue;
			}

			result += m_costs[rowIdx][j];
		}
	}
	return result;
}

void HomoriHu::ShowTable() {
	const int verticesCount = m_vertices.size();
	std::vector<std::vector<double>> table(verticesCount, std::vector<double>(verticesCount, 0));

	for (int row = 0; row < verticesCount; ++row) {
		auto vertex = std::find_if(m_vertices.begin(), m_vertices.end(), [row](const auto el) { return el.Index == row;  });
		for (int col = row + 1; col < verticesCount; ++col) {
			/*for()*/
		}
	}
}

//void