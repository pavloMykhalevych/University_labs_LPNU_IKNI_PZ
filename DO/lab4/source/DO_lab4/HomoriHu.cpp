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
	ShowTable();
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
	m_step = 1;
	std::vector<std::vector<int>> vertexGroups;

	std::vector<int> startGroup;
	for (int i = 0; i < vertexCount; ++i) {
		startGroup.push_back(i);
	}

	vertexGroups.push_back(startGroup);

	auto experienceVertex = -1;
	auto prevGroupIndex = -1;
	while (m_step < vertexCount) {
		int selectedGroupIndex = -1;

		for (int groupIndex = 0; groupIndex < vertexGroups.size(); ++groupIndex) {
			if (vertexGroups[groupIndex].size() == 1) {
				continue;
			}
			selectedGroupIndex = groupIndex;
			break;
		}

		if (prevGroupIndex != selectedGroupIndex) {
			experienceVertex = FindVertexWithMaxFlow(vertexGroups[selectedGroupIndex]);
		}

		auto selectedVertex = -1;

		for (int i = 0; i < vertexGroups[selectedGroupIndex].size(); ++i) {
			if (vertexGroups[selectedGroupIndex][i] == experienceVertex) {
				continue;
			}
			selectedVertex = vertexGroups[selectedGroupIndex][i];
			std::vector<int> new_group(1, experienceVertex);
			if (HasConnection(new_group, vertexGroups[selectedGroupIndex][i])) {
				selectedVertex = vertexGroups[selectedGroupIndex][i];
				break;
			}
		}

		double min = std::numeric_limits<double>::max();

		int groupIdx = -1;

		for (auto connectionIndex = 0; connectionIndex < m_connections.size(); connectionIndex++) {
			if (m_connections[connectionIndex].GroupIndex1 != selectedGroupIndex && m_connections[connectionIndex].GroupIndex2 != selectedGroupIndex) {
				continue;
			}
			auto connectedGroupIndex = m_connections[connectionIndex].GroupIndex1 == selectedGroupIndex ? m_connections[connectionIndex].GroupIndex2 : m_connections[connectionIndex].GroupIndex1;
			auto new_group = FindConectedGroupsToSelected(vertexGroups, connectedGroupIndex, selectedGroupIndex);
			if (!HasConnection(new_group, selectedVertex)) {
				continue;
			}
			new_group.push_back(selectedVertex);
			auto value = FindFlowSum(new_group);
			if (value < min) {
				min = value;
				groupIdx = connectedGroupIndex;
			}
		}

		std::vector<int> calculationgroup(1, selectedVertex);
		auto bestgroup = calculationgroup;
		FindInsideSelectedGroup(vertexGroups, selectedGroupIndex, experienceVertex, calculationgroup, bestgroup, min, groupIdx);

		std::vector<int> new_group(1, selectedVertex);
		auto value = FindFlowSum(new_group);
		if (value < min) {
			vertexGroups.push_back(new_group);
			vertexGroups[selectedGroupIndex].erase(std::find(vertexGroups[selectedGroupIndex].begin(), vertexGroups[selectedGroupIndex].end(), selectedVertex));
			m_connections.push_back(Connection{ selectedGroupIndex, -1,  int(vertexGroups.size() - 1), selectedVertex, value });
		}
		else {
			if (groupIdx == -1) {
				vertexGroups.push_back(bestgroup);
				for (const auto& el : bestgroup) {
					vertexGroups[selectedGroupIndex].erase(std::find(vertexGroups[selectedGroupIndex].begin(), vertexGroups[selectedGroupIndex].end(), el));
				}
				m_connections.push_back(Connection{ selectedGroupIndex, -1,  int(vertexGroups.size() - 1), -1, min });
			}
			else {
				vertexGroups.push_back(bestgroup);
				for (const auto& el : bestgroup) {
					vertexGroups[selectedGroupIndex].erase(std::find(vertexGroups[selectedGroupIndex].begin(), vertexGroups[selectedGroupIndex].end(), el));
				}
				auto it = std::find_if(m_connections.begin(), m_connections.end(), [groupIdx](const auto& connection) {
					return connection.GroupIndex1 == groupIdx || connection.GroupIndex2 == groupIdx;
					});
				if (it->GroupIndex1 == groupIdx) {
					it->GroupIndex2 = int(vertexGroups.size() - 1);
				}
				else {
					it->GroupIndex1 = int(vertexGroups.size() - 1);
				}
				m_connections.push_back(Connection{ selectedGroupIndex, -1,  int(vertexGroups.size() - 1), -1, min });
			}
		}
		prevGroupIndex = selectedGroupIndex;
		m_step++;
	}

	for (auto connectionIndex = 0; connectionIndex < m_connections.size(); connectionIndex++){
		m_connections[connectionIndex].VertexIndex1 = vertexGroups[m_connections[connectionIndex].GroupIndex1][0];
		m_connections[connectionIndex].VertexIndex2 = vertexGroups[m_connections[connectionIndex].GroupIndex2][0];
	}

}

bool HomoriHu::HasConnection(const std::vector<int>& group, int vertex) {
	for (int i = 0; i < group.size(); ++i) {
		if (m_costs[group[i]][vertex] != -1) {
			return true;
		}
	}
	return false;
}

bool HomoriHu::HasConnection(const std::vector<int>& group1, const std::vector<int>& group2) {
	for (int i = 0; i < group1.size(); ++i) {
		for (int j = 0; j < group2.size(); ++j) {
			if (m_costs[group1[i]][group2[j]] != -1) {
				return true;
			}
		}
	}
	return false;
}

int HomoriHu::FindVertexWithMaxFlow(std::vector<int> selectedGroup) {
	const int vertexCount = m_costs.size();
	std::vector<std::pair<int, double>> maxValues(vertexCount, {-1, 0});
	for (int i = 0; i < vertexCount; ++i) {
		if (std::find(selectedGroup.begin(), selectedGroup.end(), i) == selectedGroup.end()) {
			continue;
		}
		maxValues[i].first = i;
		for (int j = 0; j < vertexCount; ++j) {
			if (m_costs[i][j] == -1) {
				continue;
			}
			maxValues[i].second += m_costs[i][j];
		}
	}
	return (*std::max_element(maxValues.begin(), maxValues.end(), [](const auto& el1, const auto& el2) { return el1.second < el2.second; })).first;
}

void HomoriHu::FindInsideSelectedGroup(
	const std::vector<std::vector<int>>& vertexGroups,
	const int selectedGroupIndex,
	const int expensiveVertex,
	const std::vector<int>& calculationgroup,
	std::vector<int>& bestgroup,
	double& min,
	int& groupIdx) {
	for (auto selectedGroupVertexIndex = 0; selectedGroupVertexIndex < vertexGroups[selectedGroupIndex].size(); ++selectedGroupVertexIndex) {
		auto new_calculation_group = calculationgroup;
		if (vertexGroups[selectedGroupIndex][selectedGroupVertexIndex] == expensiveVertex) {
			continue;
		}
		if (std::find(calculationgroup.begin(), calculationgroup.end(), vertexGroups[selectedGroupIndex][selectedGroupVertexIndex]) != calculationgroup.end()) {
			continue;
		}
		if (!HasConnection(calculationgroup, vertexGroups[selectedGroupIndex][selectedGroupVertexIndex])) {
			continue;
		}
		new_calculation_group.push_back(vertexGroups[selectedGroupIndex][selectedGroupVertexIndex]);
		auto value = FindFlowSum(new_calculation_group);
		if (value < min) {
			min = value;
			groupIdx = -1;
			bestgroup = new_calculation_group;
		}
		for (auto connectionIndex = 0; connectionIndex < m_connections.size(); connectionIndex++) {
			if (m_connections[connectionIndex].GroupIndex1 != selectedGroupIndex || m_connections[connectionIndex].GroupIndex2 != selectedGroupIndex) {
				continue;
			}
			auto connectedGroupIndex = m_connections[connectionIndex].GroupIndex1 == selectedGroupIndex ? m_connections[connectionIndex].GroupIndex2 : m_connections[connectionIndex].GroupIndex1;
			auto new_group = FindConectedGroupsToSelected(vertexGroups, connectedGroupIndex, selectedGroupIndex);
			if (!HasConnection(new_group, new_calculation_group)) {
				continue;
			}
			for (int j = 0; j < new_calculation_group.size(); ++j) {
				new_group.push_back(new_calculation_group[j]);
			}
			auto value = FindFlowSum(new_group);
			if (value < min) {
				min = value;
				groupIdx = connectedGroupIndex;
				bestgroup = new_calculation_group;
			}
		}
		FindInsideSelectedGroup(vertexGroups, selectedGroupIndex, expensiveVertex, new_calculation_group, bestgroup, min, groupIdx);
	}
}

std::vector<int> HomoriHu::FindConectedGroupsToSelected(const std::vector<std::vector<int>>& vertexGroups, const int selectedGroupIndex, const int previousGroupIndex) {
	int count = 0;
	std::vector<int> result_vertices;
	for (auto connectionIndex = 0; connectionIndex < m_connections.size(); connectionIndex++) {
		if (m_connections[connectionIndex].GroupIndex1 != selectedGroupIndex && m_connections[connectionIndex].GroupIndex2 != selectedGroupIndex) {
			if ((connectionIndex == m_connections.size() - 1) && count == 0) {
				return vertexGroups[selectedGroupIndex];
			}
			continue;
		}
		if ((m_connections[connectionIndex].GroupIndex1 == selectedGroupIndex && m_connections[connectionIndex].GroupIndex2 == previousGroupIndex)
			|| (m_connections[connectionIndex].GroupIndex1 == previousGroupIndex && m_connections[connectionIndex].GroupIndex2 == selectedGroupIndex)) {
			if ((connectionIndex == m_connections.size() - 1) && count == 0) {
				return vertexGroups[selectedGroupIndex];
			}
			continue;
		}
		++count;
		auto nextGroup = m_connections[connectionIndex].GroupIndex1 == selectedGroupIndex ? m_connections[connectionIndex].GroupIndex2 : m_connections[connectionIndex].GroupIndex1;
		auto vertex_vector = FindConectedGroupsToSelected(vertexGroups, nextGroup, selectedGroupIndex);
		for (const auto& el : vertex_vector) {
			result_vertices.push_back(el);
		}
	}
	for (const auto& el : vertexGroups[selectedGroupIndex]) {
		result_vertices.push_back(el);
	}
	return result_vertices;
}

double HomoriHu::FindWay(const int selectedVertexIndex, const int previousVertexIndex, const int neededVertexIndex) {
	int count = 0;
	double result_way = -1;
	for (auto connectionIndex = 0; connectionIndex < m_connections.size(); connectionIndex++) {
		if (m_connections[connectionIndex].VertexIndex1 != selectedVertexIndex && m_connections[connectionIndex].VertexIndex2 != selectedVertexIndex) {
			if ((connectionIndex == m_connections.size() - 1) && count == 0) {
				return -1;
			}
			continue;
		}
		if ((m_connections[connectionIndex].VertexIndex1 == selectedVertexIndex && m_connections[connectionIndex].VertexIndex2 == previousVertexIndex)
			|| (m_connections[connectionIndex].VertexIndex1 == previousVertexIndex && m_connections[connectionIndex].VertexIndex2 == selectedVertexIndex)) {
			if ((connectionIndex == m_connections.size() - 1) && count == 0) {
				return -1;
			}
			continue;
		}
		if (m_connections[connectionIndex].VertexIndex1 == neededVertexIndex || m_connections[connectionIndex].VertexIndex2 == neededVertexIndex) {
			return m_connections[connectionIndex].Value;
		}
		++count;
		auto nextGroup = m_connections[connectionIndex].VertexIndex1 == selectedVertexIndex ? m_connections[connectionIndex].VertexIndex2 : m_connections[connectionIndex].VertexIndex1;
		auto value = FindWay(nextGroup, selectedVertexIndex, neededVertexIndex);
		if (value == -1) {
			continue;
		}
		result_way = m_connections[connectionIndex].Value < value ? m_connections[connectionIndex].Value : value;
	}
	return result_way;
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
	const auto vertexCount = m_costs.size();
	m_table.resize(vertexCount, std::vector<double>(vertexCount, -1.f));
	for (int i = 0; i < vertexCount; ++i) {
		for (int j = i+1; j < vertexCount; ++j) {
			for (auto connectionIndex = 0; connectionIndex < m_connections.size(); connectionIndex++) {
				if (m_connections[connectionIndex].VertexIndex1 != i && m_connections[connectionIndex].VertexIndex2 != i) {
					continue;
				}
				if ((m_connections[connectionIndex].VertexIndex1 == i && m_connections[connectionIndex].VertexIndex2 == j)
					|| (m_connections[connectionIndex].VertexIndex1 == j && m_connections[connectionIndex].VertexIndex2 == i)) {
					m_table[i][j] = m_connections[connectionIndex].Value;
					break;
				}
				auto connectedGroupIndex = m_connections[connectionIndex].VertexIndex1 == i ? m_connections[connectionIndex].VertexIndex2 : m_connections[connectionIndex].VertexIndex1;
				auto way = FindWay(connectedGroupIndex, i, j);
				if(m_table[i][j] == -1 && way != -1){
					m_table[i][j] = way < m_connections[connectionIndex].Value ? way : m_connections[connectionIndex].Value;
				}
			}
		}
	}
	for (int i = 0; i < vertexCount; ++i) {
		for (int j = 0; j < i; ++j) {
			m_table[i][j] = m_table[j][i];
		}
	}

	std::cout << "Result table:\n";
	for (int i = 0; i < vertexCount; ++i) {
		std::cout << std::setprecision(1) << std::left << std::fixed << std::setw(4) << "[";
		for (int j = 0; j < vertexCount; ++j) {
			std::cout << std::setprecision(1) << std::left << std::fixed << std::setw(7) << m_table[i][j];
		}
		std::cout << "]\n";
	}
}