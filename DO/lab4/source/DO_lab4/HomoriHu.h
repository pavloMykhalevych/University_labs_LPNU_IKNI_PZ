#pragma once

#include <string>
#include <vector>

#include "Connection.h"

class HomoriHu
{
public:
	void Start();

private:
	void CreateProblem(const bool fromConsole = false, std::string fileName = "lab6_main.json");

	void BuildRoute();

	void ShowTable();

	int FindVertexWithMaxFlow(std::vector<int> selectedGroup);

	void FindInsideSelectedGroup(const std::vector<std::vector<int>>& vertexGroups, const int selectedGroupIndex,
		const int expensiveVertex, const std::vector<int>& calculationgroup,
		std::vector<int>& bestgroup, double& min, int& groupIdx);

	//void FindVertexFromStart(double& value, int& vertexidx, int& startVertex);

	double FindFlowSum(const std::vector<int>& group);

	bool HasConnection(const std::vector<int>& group, int vertex);

	bool HasConnection(const std::vector<int>& group1, const std::vector<int>& group2);

	double FindWay(const int selectedVertexIndex, const int previousVertexIndex, const int neededVertexIndex);

	std::vector<int> FindConectedGroupsToSelected(const std::vector<std::vector<int>>& vertexGroups,
		const int selectedGroupIndex, const int previousGroupIndex);

	int m_startPeek;
	int m_endPeek;
	std::vector<std::vector<double>> m_costs;
	std::vector<std::vector<double>> m_table;

	std::vector<int> m_notUsedVertices;
	std::vector<int> m_usedVertices;

	std::vector<Connection> m_connections;
	int m_step;
};
