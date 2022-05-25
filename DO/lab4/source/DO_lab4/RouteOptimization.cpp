//#define NOMINMAX
//
//#include "RouteOptimization.h"
//
//#include <json.h>
//
//#include <iostream>
//#include <algorithm>
//#include <iomanip>
//#include <fstream>
//#include <sstream>
//#include <limits>
//
//#include "color.hpp"
//
//void RouteOptimization::Start() {
//	CreateProblem(false, "lab6_13.json");
//	FloydFindRoute();
//	DejkstraStart();
//}
//
//void RouteOptimization::CreateProblem(const bool fromConsole, std::string fileName) {
//	if (fromConsole) {
//		std::cout << "Enter number of peeks:";
//		int peeksNumber;
//		std::cin >> peeksNumber;
//		m_costs.resize(peeksNumber, std::vector<double>(peeksNumber, 0));
//		std::cout << "Enter costs:";
//		for (int i = 0; i < peeksNumber; ++i) {
//			for (int j = 0; j < peeksNumber; ++j) {
//				std::cout << "c[" << i + 1 << "][" << j + 1 <<  "] = ";
//				std::cin >> m_costs[i][j];
//			}
//		}
//		std::cout << "Enter the start peek:";
//		std::cin >> m_startPeek;
//		std::cout << "Enter the end peek:";
//		std::cin >> m_endPeek;
//	}
//	else {
//		std::ifstream jsonFile(fileName);
//		if (jsonFile.fail())
//		{
//			throw std::runtime_error("File was not found.\n");
//		}
//		nlohmann::json parsedJson = nlohmann::json::parse(jsonFile);
//		const auto& parsedJsonCosts = parsedJson.at("Costs");
//		const auto peeksCount = parsedJson.at("PeeksCount").get<int>();
//		m_costs.resize(peeksCount, std::vector<double>(peeksCount, 0));
//
//		for (int i = 0; i < peeksCount; ++i) {
//			for (int j = 0; j < peeksCount; ++j) {
//				m_costs[i][j] = parsedJsonCosts[i][j].get<double>();
//			}
//		}
//		m_startPeek = parsedJson.at("StartPeek").get<int>();
//		m_endPeek = parsedJson.at("EndPeek").get<int>();
//	}
//}
//
//void RouteOptimization::PrintFloyd(const int iteration, std::vector<std::pair<int, int>> underlineIndices) {
//	std::cout << "\nIteration " << iteration << ":\n";
//	for (int rowIndex = 0; rowIndex < m_costs.size(); ++rowIndex) {
//		if (rowIndex == 0) {
//			std::cout << std::setw(5) << std::left << "D: [";
//		}
//		else {
//			std::cout << std::setw(5) << "   [";
//		}
//		for (int colIndex = 0; colIndex < m_costs.size(); ++colIndex) {
//			auto underline = std::find_if(underlineIndices.begin(), underlineIndices.end(),
//				[=](const auto& indices)
//				{
//					return (rowIndex == indices.first) && (colIndex == indices.second);
//				});
//			if (underline != underlineIndices.end()) {
//				std::ostringstream ss;
//				ss << std::setprecision(1) << std::left << std::fixed << m_floyd_d[rowIndex][colIndex];
//				std::cout << std::setw(7) << dye::red((m_floyd_d[rowIndex][colIndex] == std::numeric_limits<double>::max()) ? "-" : ss.str());
//			}
//			else {
//				std::ostringstream ss;
//				ss << std::setprecision(1) << std::left << std::fixed << m_floyd_d[rowIndex][colIndex];
//				std::cout << std::setw(7) << ((m_floyd_d[rowIndex][colIndex] == std::numeric_limits<double>::max()) ? "-" : ss.str());
//			}
//			if (colIndex < m_costs.size() - 1) {
//				std::cout << ", ";
//			}
//		}
//		std::cout << std::setw(7) << std::left << " ] ";
//		if (rowIndex == 0) {
//			std::cout << std::setw(5) << std::left << "R: [";
//		}
//		else {
//			std::cout << std::setw(5) << "";
//		}
//		for (int colIndex = 0; colIndex < m_costs.size(); ++colIndex) {
//			auto underline = std::find_if(underlineIndices.begin(), underlineIndices.end(),
//				[=](const auto& indices)
//				{
//					return (rowIndex == indices.first) && (colIndex == indices.second);
//				});
//			if (underline != underlineIndices.end()) {
//				std::ostringstream ss;
//				ss << std::setw(7) << std::left << m_floyd_r[rowIndex][colIndex];
//				std::cout << dye::red(ss.str());
//			}
//			else {
//				std::cout << std::setw(7) << std::left << m_floyd_r[rowIndex][colIndex];
//			}
//			if (colIndex < m_costs.size() - 1) {
//				std::cout << ", ";
//			}
//		}
//		std::cout << std::left << " ] \n";
//	}
//}
//
//
//void RouteOptimization::FloydCreateTables() {
//	m_floyd_d = m_costs;
//	m_floyd_r.resize(m_costs.size(), std::vector<int>(m_costs.size(), 0));
//	for (int i = 0; i < m_costs.size(); ++i) {
//		for (int j = 0; j < m_costs.size(); ++j) {
//			if (i == j) {
//				m_floyd_d[i][j] = 0;
//				m_floyd_r[i][j] = 0;
//				continue;
//			}
//			if (m_floyd_d[i][j] == 0) {
//				m_floyd_d[i][j] = std::numeric_limits<double>::max();
//			}
//			m_floyd_r[i][j] = i + 1;
//		}
//	}
//
//	PrintFloyd(0);
//}
//
//void RouteOptimization::FloydGoToNextTables(const int basisPeek) {
//	if (basisPeek >= m_floyd_d.size()) {
//		return;
//	}
//
//	std::vector<int> unusedRows;
//	std::vector<int> unusedCols;
//	std::vector<std::pair<int, int>> underlineIndices;
//
//	for (int rowIndex = 0; rowIndex < m_costs.size(); ++rowIndex) {
//		if (m_floyd_d[rowIndex][basisPeek] == std::numeric_limits<double>::max()) {
//			unusedRows.push_back(rowIndex);
//		}
//	}
//
//	for (int colIndex = 0; colIndex < m_costs.size(); ++colIndex) {
//		if (m_floyd_d[basisPeek][colIndex] == std::numeric_limits<double>::max()) {
//			unusedCols.push_back(colIndex);
//		}
//	}
//
//	for (int rowIndex = 0; rowIndex < m_costs.size(); ++rowIndex) {
//		for (int colIndex = 0; colIndex < m_costs.size(); ++colIndex) {
//			if (rowIndex == colIndex || rowIndex == basisPeek || colIndex == basisPeek
//				|| (std::find(unusedRows.begin(), unusedRows.end(), rowIndex) != unusedRows.end())
//				|| (std::find(unusedCols.begin(), unusedCols.end(), colIndex) != unusedCols.end())) {
//				continue;
//			}
//			auto new_d = std::min(m_floyd_d[rowIndex][colIndex], (m_floyd_d[rowIndex][basisPeek] + m_floyd_d[basisPeek][colIndex]));
//			if (new_d < m_floyd_d[rowIndex][colIndex]) {
//				m_floyd_d[rowIndex][colIndex] = new_d;
//				m_floyd_r[rowIndex][colIndex] = m_floyd_r[basisPeek][colIndex];
//				underlineIndices.push_back(std::pair<int, int>(rowIndex, colIndex));
//			}
//		}
//	}
//
//	PrintFloyd(basisPeek+1, underlineIndices);
//
//	FloydGoToNextTables(basisPeek + 1);
//}
//
//void RouteOptimization::FloydFindRoute() {
//	FloydCreateTables();
//	FloydGoToNextTables(0);
//	std::cout << "\nRoute from " << m_startPeek << " to " << m_endPeek << " :\n";
//	int i = m_startPeek - 1;
//	int j = m_endPeek - 1;
//	std::cout << "d = " << m_floyd_d[i][j] << "\n";
//	std::vector<int> route;
//	while (m_floyd_r[i][j] != m_startPeek) {
//		route.push_back(m_floyd_r[i][j]);
//		j = m_floyd_r[i][j] - 1;
//	}
//	std::cout << "Route: " << m_startPeek << " -> ";
//	for (int m = route.size() - 1; m >= 0; --m) {
//		std::cout << route[m] << " -> ";
//	}
//	std::cout << m_endPeek << "\n";
//}
//
//void RouteOptimization::PrintDejkstra() {
//	std::cout << "\n";
//	for (int i = 0; i < m_dejkstra_tree.size(); ++i) {
//		std::cout << "| " << std::setw(10) << std::left << i + 1;
//	}
//	std::cout << "|\n";
//	for (int i = 0; i < m_dejkstra_tree.size(); ++i) {
//		std::ostringstream ss;
//		ss << std::setprecision(1) << std::left << std::fixed << m_dejkstra_tree[i].first;
//		std::cout << "| " << std::setw(10) << ((m_dejkstra_tree[i].first == std::numeric_limits<double>::max()) ? "-" : ss.str());
//	}
//	std::cout << "|\n";
//	for (int i = 0; i < m_dejkstra_tree.size(); ++i) {
//		std::cout << "| " << std::setw(10) << std::left << m_dejkstra_tree[i].second + 1;
//	}
//	std::cout << "|\n";
//}
//
//void RouteOptimization::DejkstraCreate() {
//	m_dejkstra_tree.resize(m_costs.size(), std::pair<double, int>(std::numeric_limits<double>::max(), 0));
//	m_dejkstra_tree[0].first = 0;
//}
//
//void RouteOptimization::DeikstraFindRoute() {
//	std::cout << "\nRoute from " << m_startPeek << " to " << m_endPeek << " :\n";
//	int i = m_startPeek - 1;
//	int j = m_endPeek - 1;
//	std::cout << "d = " << m_dejkstra_tree[j].first << "\n";
//	std::vector<int> route;
//	while (m_dejkstra_tree[j].second != i) {
//		route.push_back(m_dejkstra_tree[j].second + 1);
//		j = m_dejkstra_tree[j].second;
//	}
//	std::cout << "Route: " << m_startPeek << " -> ";
//	for (int m = route.size() - 1; m >= 0; --m) {
//		std::cout << route[m] << " -> ";
//	}
//	std::cout << m_endPeek << "\n";
//}
//
//void RouteOptimization::DejkstraStart() {
//	DejkstraCreate();
//	DejkstraGoToNextPeek(0);
//	PrintDejkstra();
//	DeikstraFindRoute();
//}
//
//void RouteOptimization::DejkstraGoToNextPeek(const int looked_peek) {
//	m_looked_peeks.push_back(looked_peek);
//	auto min = std::numeric_limits<double>::max();
//	auto min_index = -1;
//	for (int i = 0; i < m_dejkstra_tree.size(); ++i) {
//		if (std::find(m_looked_peeks.begin(), m_looked_peeks.end(), i) != m_looked_peeks.end()) {
//			continue;
//		}
//		auto new_d = std::min(m_dejkstra_tree[i].first,
//			((m_costs[looked_peek][i] == 0) ? std::numeric_limits<double>::max() : m_dejkstra_tree[looked_peek].first + m_costs[looked_peek][i]));
//		if (new_d < m_dejkstra_tree[i].first) {
//			m_dejkstra_tree[i].first = new_d;
//			m_dejkstra_tree[i].second = looked_peek;
//		}
//		if (min > m_dejkstra_tree[i].first) {
//			min = m_dejkstra_tree[i].first;
//			min_index = i;
//		}
//	}
//	std::cout << std::endl;
//	PrintDejkstra();
//	std::cout << "\ny = " << min_index + 1 << std::endl;
//	if (min_index == -1 || min_index == m_endPeek - 1) {
//		std::cout << "\nEnd.\n";
//		return;
//	}
//	DejkstraGoToNextPeek(min_index);
//}
