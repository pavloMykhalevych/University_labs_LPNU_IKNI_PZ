//#pragma once
//
//#include <string>
//#include <vector>
//
//class RouteOptimization
//{
//public:
//	void Start();
//
//private:
//	void CreateProblem(const bool fromConsole = false, std::string fileName = "lab6_main.json");
//
//	void PrintFloyd(const int iteration, std::vector<std::pair<int, int>> underlineIndices = std::vector<std::pair<int, int>>());
//	void FloydCreateTables();
//	void FloydGoToNextTables(const int basisPeek);
//	void FloydFindRoute();
//
//	void PrintDejkstra();
//	void DejkstraCreate();
//	void DeikstraFindRoute();
//	void DejkstraStart();
//	void DejkstraGoToNextPeek(const int looked_peek);
//
//	int m_startPeek;
//	int m_endPeek;
//	std::vector<std::vector<double>> m_costs;
//
//	std::vector<std::vector<double>> m_floyd_d;
//	std::vector<std::vector<int>> m_floyd_r;
//
//	std::vector<std::pair<double, int>> m_dejkstra_tree;
//	std::vector<int> m_looked_peeks;
//};
//
