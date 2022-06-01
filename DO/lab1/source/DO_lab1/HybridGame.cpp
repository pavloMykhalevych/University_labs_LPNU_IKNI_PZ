#include "HybridGame.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>

void HybridGame::Start() {
	CreateProblem(false, "Hybrid_1.json");
	if (FindBoundaries()) {
		return;
	}
	SimplifyProblem();
	CreateSymplexTables();
	ShowResults();
}

void HybridGame::CreateProblem(const bool fromConsole, std::string fileName) {
	if (fromConsole) {
		std::cout << "Enter number of A strategy:";
		int strategyA;
		std::cin >> strategyA;
		std::cout << "Enter number of B strategy:";
		int strategyB;
		std::cin >> strategyB;
		m_table.resize(strategyA, std::vector<int>(strategyB, 0));
		std::cout << "Enter costs:";
		for (int i = 0; i < strategyA; ++i) {
			for (int j = 0; j < strategyB; ++j) {
				std::cout << "a[" << i + 1 << "][" << j + 1 << "] = ";
				std::cin >> m_table[i][j];
			}
		}
	}
	else {
		std::ifstream jsonFile(fileName);
		if (jsonFile.fail())
		{
			throw std::runtime_error("File was not found.\n");
		}
		nlohmann::json parsedJson = nlohmann::json::parse(jsonFile);
		const auto parsedJsonStrategyACount = parsedJson.at("StrategyACount").get<int>();
		const auto parsedJsonStrategyBCount = parsedJson.at("StrategyBCount").get<int>();
		const auto matrix = parsedJson.at("Matrix");
		m_table.resize(parsedJsonStrategyACount, std::vector<int>(parsedJsonStrategyBCount, 0));

		for (int i = 0; i < parsedJsonStrategyACount; ++i) {
			for (int j = 0; j < parsedJsonStrategyBCount; ++j) {
				m_table[i][j] = matrix[i][j].get<int>();
			}
		}
	}
}


bool HybridGame::FindBoundaries() {
	std::vector<int> maxInCols = std::vector<int>(m_table[0].size(), std::numeric_limits<int>::min());
	std::vector<int> minInRows = std::vector<int>(m_table.size(), std::numeric_limits<int>::max());
	for (int i = 0; i < m_table.size(); ++i) {
		for (int j = 0; j < m_table[0].size(); ++j) {
			if (m_table[i][j] < minInRows[i]) {
				minInRows[i] = m_table[i][j];
			}
			if (m_table[i][j] > maxInCols[j]) {
				maxInCols[j] = m_table[i][j];
			}
		}
	}
	auto lowBoundary = *std::max_element(minInRows.begin(), minInRows.end());
	auto highBoundary = *std::min_element(maxInCols.begin(), maxInCols.end());
	if (lowBoundary == highBoundary) {
		std::cout << "\nProblem is solved with cost = " << highBoundary << "\n";
		return true;
	}
	return false;
}

void HybridGame::SimplifyProblem() {
	std::vector<int> removedRows;
	std::vector<int> removedCols;
	for (int mainRow = 0; mainRow < m_table.size(); ++mainRow) {
		if (std::find(removedRows.begin(), removedRows.end(), mainRow) != removedRows.end()) {
			continue;
		}
		for (int i = 0; i < m_table.size(); ++i) {
			if (i == mainRow) {
				continue;
			}
			if (std::find(removedRows.begin(), removedRows.end(), i) != removedRows.end()) {
				continue;
			}
			int count = 0;
			for (int j = 0; j < m_table[0].size(); ++j) {
				if (m_table[i][j] <= m_table[mainRow][j]) {
					++count;
				}
			}
			if (count == m_table[0].size()) {
				removedRows.push_back(i);
			}
			else if (count == 0) {
				removedRows.push_back(mainRow);
				break;
			}
		}
	}

	for (int mainCol = 0; mainCol < m_table[0].size(); ++mainCol) {
		if (std::find(removedCols.begin(), removedCols.end(), mainCol) != removedCols.end()) {
			continue;
		}
		for (int i = 0; i < m_table[0].size(); ++i) {
			if (i == mainCol) {
				continue;
			}
			if (std::find(removedCols.begin(), removedCols.end(), i) != removedCols.end()) {
				continue;
			}
			int count = 0;
			for (int j = 0; j < m_table.size(); ++j) {
				if (m_table[j][i] <= m_table[j][mainCol]) {
					++count;
				}
			}
			if (count == m_table.size()) {
				removedCols.push_back(i);
			}
			else if (count == 0) {
				removedCols.push_back(mainCol);
				break;
			}
		}
	}
	for (int i = 0; i < m_table.size(); ++i) {
		if (std::find(removedRows.begin(), removedRows.end(), i) != removedRows.end()) {
			continue;
		}
		std::vector<int> row;
		for (int j = 0; j < m_table[0].size(); ++j) {
			if (std::find(removedCols.begin(), removedCols.end(), j) != removedCols.end()) {
				continue;
			}
			row.push_back(m_table[i][j]);
		}
		m_simplifiedTable.push_back(row);
	}
}

void HybridGame::CreateSymplexTables() {
	m_syntexSolver.CreateProblem(m_simplifiedTable);
	auto result = m_syntexSolver.Start();
	m_v = 1 / result[0];
	m_p.reserve(m_simplifiedTable.size());
	m_q.reserve(m_simplifiedTable[0].size());
	for (int i = 1; i <= m_simplifiedTable[0].size(); ++i) {
		m_q.push_back(result[i]);
	}
	for (int i = m_simplifiedTable[0].size()+1; i <= m_simplifiedTable[0].size() + m_simplifiedTable.size(); ++i) {
		m_p.push_back(result[i]);
	}
}

void HybridGame::ShowResults() {
	std::cout << "\n\nResults\n\nTable:\n";
	for (int i = 0; i < m_simplifiedTable.size(); ++i) {
		std::cout << std::left << std::fixed << std::setw(4) << "[";
		for (int j = 0; j < m_simplifiedTable[0].size(); ++j) {
			std::cout << std::setprecision(2) << std::left << std::fixed << std::setw(7) << m_simplifiedTable[i][j];
		}
		std::cout << "]\n";
	}
	std::cout << "\n\nGame Price\n\nv = [1/F] = " << m_v;
	std::cout << "\n\nProbabilities:\n\nFor player A:\n";
	for (int i = 0; i < m_p.size(); ++i) {
		std::cout << "A[" << i + 1 << "] = " << m_p[i] * m_v << "\n";
	}
	std::cout << "\nFor player B:\n";
	for (int i = 0; i < m_q.size(); ++i) {
		std::cout << "B[" << i + 1 << "] = " << m_q[i] * m_v << "\n";
	}
}