#pragma once

#include <string>
#include <vector>

#include "Vertex.h"

class HomoriHu
{
public:
	void Start();

private:
	void CreateProblem(const bool fromConsole = false, std::string fileName = "lab6_main.json");

	void BuildRoute();

	void ShowTable();

	void FindVertexWithMaxFlow(double& value, int& vertexidx);

	void FindVertexFromStart(double& value, int& vertexidx, int& startVertex);

	double FindFlowSum(const std::vector<int>& group);

	bool HasConnection(const std::vector<int>& group, int vertex);

	int m_startPeek;
	int m_endPeek;
	std::vector<std::vector<double>> m_costs;

	std::vector<int> m_notUsedVertices;
	std::vector<int> m_usedVertices;

	std::vector<Vertex> m_vertices;
	int m_step;
};
