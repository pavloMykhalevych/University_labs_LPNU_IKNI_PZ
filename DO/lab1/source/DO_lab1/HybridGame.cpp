#include "HybridGame.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>

void HybridGame::Start() {
	CreateProblem(false, "Hybrid_2.json");
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
	bool can_continue = true;
	m_simplifiedTable = m_table;
	while (can_continue) {
		removedRows.clear();
		for (int mainRow = 0; mainRow < m_simplifiedTable.size(); ++mainRow) {
			if (std::find(removedRows.begin(), removedRows.end(), mainRow) != removedRows.end()) {
				continue;
			}
			for (int i = 0; i < m_simplifiedTable.size(); ++i) {
				if (i == mainRow) {
					continue;
				}
				if (std::find(removedRows.begin(), removedRows.end(), i) != removedRows.end()) {
					continue;
				}
				int count = 0;
				for (int j = 0; j < m_simplifiedTable[0].size(); ++j) {
					if (m_simplifiedTable[i][j] <= m_simplifiedTable[mainRow][j]) {
						++count;
					}
				}
				if (count == m_simplifiedTable[0].size()) {
					removedRows.push_back(i);
				}
				else if (count == 0) {
					removedRows.push_back(mainRow);
					break;
				}
			}
		}
		auto rowCount = m_simplifiedTable.size();
		auto colCount = m_simplifiedTable[0].size();
		auto prevsimplifiedTable = m_simplifiedTable;
		m_simplifiedTable.clear();
		for (int i = 0; i < rowCount; ++i) {
			if (std::find(removedRows.begin(), removedRows.end(), i) != removedRows.end()) {
				continue;
			}
			std::vector<int> row;
			for (int j = 0; j < colCount; ++j) {
				row.push_back(prevsimplifiedTable[i][j]);
			}
			m_simplifiedTable.push_back(row);
		}
		m_removedRows.insert(m_removedRows.end(), removedRows.begin(), removedRows.end());
		removedCols.clear();
		for (int mainCol = 0; mainCol < colCount; ++mainCol) {
			if (std::find(removedCols.begin(), removedCols.end(), mainCol) != removedCols.end()) {
				continue;
			}
			for (int i = 0; i < m_simplifiedTable[0].size(); ++i) {
				if (i == mainCol) {
					continue;
				}
				if (std::find(removedCols.begin(), removedCols.end(), i) != removedCols.end()) {
					continue;
				}
				int count = 0;
				for (int j = 0; j < m_simplifiedTable.size(); ++j) {
					if (m_simplifiedTable[j][i] >= m_simplifiedTable[j][mainCol]) {
						++count;
					}
				}
				if (count == m_simplifiedTable.size()) {
					removedCols.push_back(i);
				}
				else if (count == 0) {
					removedCols.push_back(mainCol);
					break;
				}
			}
		}
		rowCount = m_simplifiedTable.size();
		colCount = m_simplifiedTable[0].size();
		prevsimplifiedTable = m_simplifiedTable;
		m_simplifiedTable.clear();
		for (int i = 0; i < rowCount; ++i) {
			std::vector<int> row;
			for (int j = 0; j < colCount; ++j) {
				if (std::find(removedCols.begin(), removedCols.end(), j) != removedCols.end()) {
					continue;
				}
				row.push_back(prevsimplifiedTable[i][j]);
			}
			m_simplifiedTable.push_back(row);
		}
		m_removedCols.insert(m_removedCols.end(), removedCols.begin(), removedCols.end());
		if (removedRows.empty() || removedCols.empty()) {
			can_continue = false;
		}
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
	std::vector<int> rowIdx;
	std::vector<int> colIdx;
	for (int i = 0; i < m_table.size(); ++i) {
		if (std::find(m_removedRows.begin(), m_removedRows.end(), i) == m_removedRows.end()) {
			rowIdx.push_back(i + 1);
		}
	}
	for (int i = 0; i < m_table[0].size(); ++i) {
		if (std::find(m_removedCols.begin(), m_removedCols.end(), i) == m_removedCols.end()) {
			colIdx.push_back(i + 1);
		}
	}
	std::cout << "\n\nProbabilities:\n\nFor player A:\n";
	for (int i = 0; i < m_p.size(); ++i) {
		std::cout << "A[" << rowIdx[i] << "] = " << m_p[i] * m_v << "\n";
	}
	std::cout << "\nFor player B:\n";
	for (int i = 0; i < m_q.size(); ++i) {
		std::cout << "B[" << colIdx[i] << "] = " << m_q[i] * m_v << "\n";
	}
}