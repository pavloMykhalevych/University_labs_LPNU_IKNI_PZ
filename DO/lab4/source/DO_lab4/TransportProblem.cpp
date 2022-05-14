#include "TransportProblem.h"

#include <json.h>

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "color.hpp"

void TransportProblem::Start() {
	CreateProblem(false, "main_2.json");
	if (!IsClosed()) {
		std::cout << "Proble is not closed type!";
		return;
	}
	FindInitialFucntion();
	CalculateFunction("Result function after finding supporting plan:");
	ShowTable();
	CalculatePotensials();
	ShowTable();
	while (FindLoopAndRecalculate()) {
		CalculatePotensials();
		ShowTable();
	}
	CalculateFunction("Found optimal:");
}

void TransportProblem::StartRent() {
	CreateProblem();
	if (!IsClosed()) {
		std::cout << "Proble is not closed type!";
	}
	FindInitialFucntion();
	CalculateFunction("Result function after finding supporting plan:");
	ShowTable();
	CalculatePotensials();
	ShowTable();
	while (FindLoopAndRecalculate()) {
		CalculatePotensials();
		ShowTable();
	}
	CalculateFunction("Found optimal:");
}

void TransportProblem::CreateProblem(const bool fromConsole, std::string fileName) {
	if (fromConsole) {
		std::cout << "Enter number of supply locations:";
		int suplyNumber;
		std::cin >> suplyNumber;
		m_a_rows.resize(suplyNumber);
		std::cout << "Enter supplies:";
		for (int i = 0; i < suplyNumber; ++i) {
			std::cout << "A[" << i+1 << "] = ";
			std::cin >> m_a_rows[i];
		}
		std::cout << "Enter number of demand locations:";
		int demandNumber;
		std::cin >> demandNumber;
		m_b_cols.resize(demandNumber);
		std::cout << "Enter demands:";
		for (int i = 0; i < demandNumber; ++i) {
			std::cout << "B[" << i +1 << "] = ";
			std::cin >> m_b_cols[i];
		}
		m_table.resize(suplyNumber, std::vector<Cell>(demandNumber, Cell{ 0,0,false }));
		for (int i = 0; i < suplyNumber; ++i) {
			for (int j = 0; j < demandNumber; ++j) {
				std::cout << "a[" << i + 1 << "][" << j + 1 << "] = ";
				std::cin >> m_table[i][j].top;
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
		const auto& parsedJsonSupply = parsedJson.at("Supply");
		m_a_rows.resize(parsedJsonSupply.at("Count").get<int>());
		for (int i = 0; i < m_a_rows.size(); ++i) {
			m_a_rows[i] = parsedJsonSupply.at("values")[i].get<double>();
		}
		const auto& parsedJsonDemand = parsedJson.at("Demand");
		m_b_cols.resize(parsedJsonDemand.at("Count").get<int>());
		for (int i = 0; i < m_b_cols.size(); ++i) {
			m_b_cols[i] = parsedJsonDemand.at("values")[i].get<double>();
		}
		m_table.resize(m_a_rows.size(), std::vector<Cell>(m_b_cols.size(), Cell{ 0,0,false }));
		const auto& parsedJsontableValues = parsedJson.at("TableValues");
		for (int i = 0; i < m_a_rows.size(); ++i) {
			for (int j = 0; j < m_b_cols.size(); ++j) {
				m_table[i][j].top = parsedJsontableValues[i][j].get<double>();
			}
		}
	}
	m_v_rows.resize(m_a_rows.size(), Potential{ 0, false });
	m_u_cols.resize(m_b_cols.size(), Potential{ 0, false });
}

bool TransportProblem::IsClosed() {
	double sum1 = 0;
	double sum2 = 0;
	for (auto a : m_a_rows) {
		sum1 += a;
	}
	for (auto b : m_b_cols) {
		sum2 += b;
	}
	return sum1 == sum2;
}

void TransportProblem::ShowTable(const std::string& message) {
	std::cout << "\n" + message;
	std::cout << "\n";
	std::cout << std::setw(15 + 16*m_b_cols.size()) << std::setfill('-') << "";
	//other rows
	std::cout << "\n";
	std::cout << std::setfill(' ');
	//1 row
	std::cout << std::setw(15) << std::left << "|";
	for (int i = 0; i < m_u_cols.size(); ++i) {
		std::cout << "|b[" << std::to_string(i + 1) << "] = " << std::setw(8) << std::setprecision(3) << std::left << m_u_cols[i].Value;
	}
	std::cout << "|";
	std::cout << "\n";
	std::cout << std::setw(15 + 16 * m_b_cols.size()) << std::setfill('-') << "";
	//other rows
	std::cout << "\n";
	std::cout << std::setfill(' ');
	for (int rowIndex = 0; rowIndex < m_v_rows.size(); ++rowIndex) {
		std::cout << "|a[" + std::to_string(rowIndex + 1) + "] = " << std::setw(7) << std::setprecision(3) << std::left << m_v_rows[rowIndex].Value;
		for (int colIndex = 0; colIndex < m_u_cols.size(); ++colIndex) {
			std::cout << "|" << std::setw(15) << std::setprecision(3) << std::left << m_table[rowIndex][colIndex].top;
		}
		std::cout << "|";
		std::cout << "\n";

		std::cout << std::setw(15) << std::left << "|";
		for (int colIndex = 0; colIndex < m_u_cols.size(); ++colIndex) {
			std::ostringstream ss;
			ss << std::setw(15) << std::setprecision(3) << std::right << m_table[rowIndex][colIndex].bottom;
			auto value = m_table[rowIndex][colIndex].used ? dye::red(ss.str()) : dye::green(ss.str());
			std::cout << "|" << value;
		}
		std::cout << "|";
		std::cout << "\n";
		std::cout << std::setw(15 + 16 * m_b_cols.size()) << std::setfill('-') << "";
		std::cout << "\n";
		std::cout << std::setfill(' ');
	}
	std::cout << "\n";
}

void TransportProblem::CalculateFunction(std::string mes) {
	std::cout << "\n"+mes+"\n";
	m_result = 0;
	for (int i = 0; i < m_table.size(); ++i) {
		for (int j = 0; j < m_table[i].size(); ++j) {
			if (m_table[i][j].used) {
				m_result += m_table[i][j].top * m_table[i][j].bottom;
			}
		}
	}
	std::cout << "\nF = " << m_result << "\n";
}

bool TransportProblem::FindLoopAndRecalculate() {
	double max = -1;
	int maxRowIndex = -1;
	int maxColIndex = -1;
	for (int i = 0; i < m_table.size(); ++i) {
		for (int j = 0; j < m_table[i].size(); ++j) {
			if (m_table[i][j].used) {
				continue;
			}
			if (m_table[i][j].bottom >= 0 && max < m_table[i][j].bottom) {
				max = m_table[i][j].bottom;
				maxRowIndex = i;
				maxColIndex = j;
			}
		}
	}
	if (max == -1) {
		return false;
	}
	std::vector<LoopCellInfo> path;
	path.push_back(LoopCellInfo{ m_table[maxRowIndex][maxColIndex], true, maxRowIndex, maxColIndex });
	m_table[maxRowIndex][maxColIndex].used = true;
	auto resultLoop = FindNextElementInLoop(path, true);

	if (resultLoop.first) {
		path = resultLoop.second;
	}
	else {
		return false;
	}

	std::cout << "\nPath:\n";
	for (auto& cell : path)
	{
		std::cout << "a[" << cell.RowIndex + 1 << "][" << cell.ColIndex + 1 << "] =>";
	}
	std::cout << "\n";

	double min = 10000;
	double minRowIndex = -1;
	double minColIndex = -1;
	for (const auto& cell : path) {
		if (!cell.Plus) {
			if (min > cell.Cell.bottom) {
				min = cell.Cell.bottom;
				minRowIndex = cell.RowIndex;
				minColIndex = cell.ColIndex;
			}
		}
	}
	for (const auto& cell : path) {
		m_table[minRowIndex][minColIndex].used = false;
		cell.Cell.bottom = cell.Plus ? cell.Cell.bottom + min : cell.Cell.bottom - min;
	}
	m_table[maxRowIndex][maxColIndex].bottom = min;
	return true;
}

std::pair<bool, std::vector<LoopCellInfo>> TransportProblem::FindNextElementInLoop(const std::vector<LoopCellInfo>& path, bool horizontal) {
	std::vector<LoopCellInfo> neighbors;
	neighbors = FindNeigbors(path.back(), horizontal);
	if (path.size() == 1 && neighbors.empty()) {
		horizontal = !horizontal;
		neighbors = FindNeigbors(path.back(), horizontal);
	}
	else if (neighbors.empty()) {
		return std::pair<bool, std::vector<LoopCellInfo>>(false, path);
	}
	horizontal = !horizontal;

	const auto& start = path.front();

	for (auto a : neighbors) {
		if ((a.RowIndex == start.RowIndex) && (a.ColIndex == start.ColIndex) && (a.Cell.top == start.Cell.top)
			&& (a.Cell.bottom == start.Cell.bottom) && path.size() > 2) {
			return std::pair<bool, std::vector<LoopCellInfo>>(true, path);
		}
	}

	for (auto& loopCellInfo : neighbors) {

		auto newPath = path;
		newPath.push_back(loopCellInfo);
		auto result = FindNextElementInLoop(newPath, horizontal);
		if (result.first) {
			return result;
		}
	}
	return std::pair<bool, std::vector<LoopCellInfo>>(false, path);
}

std::vector<LoopCellInfo> TransportProblem::FindNeigbors(LoopCellInfo loopCellInfo, bool horizontal) {
	std::vector<LoopCellInfo> neighbors;
	if (horizontal) {
		for (int colIndex = 0; colIndex < m_u_cols.size(); ++colIndex) {
			if (m_table[loopCellInfo.RowIndex][colIndex].used) {
				if (loopCellInfo.ColIndex == colIndex) {
					continue;
				}
				neighbors.push_back(LoopCellInfo{ m_table[loopCellInfo.RowIndex][colIndex], !loopCellInfo.Plus, loopCellInfo.RowIndex,colIndex });
			}
		}
	}
	else {
		for (int rowIndex = 0; rowIndex < m_v_rows.size(); ++rowIndex) {
			if (m_table[rowIndex][loopCellInfo.ColIndex].used) {
				if (loopCellInfo.RowIndex == rowIndex) {
					continue;
				}
				neighbors.push_back(LoopCellInfo{ m_table[rowIndex][loopCellInfo.ColIndex], !loopCellInfo.Plus, rowIndex,loopCellInfo.ColIndex });
			}
		}
	}
	return neighbors;
}

void TransportProblem::FindInitialFucntion() {
	std::vector<int> usedRows;
	std::vector<int> usedColumns;
	int count = 0;
	bool foundInitial = false;
	while (!foundInitial) {
		double min = 10000000000.f;
		int min_i = -1;
		int min_j = -1;
		for (int i = 0; i < m_table.size(); ++i) {
			if (std::find(usedRows.begin(), usedRows.end(), i) != usedRows.end()) {
				continue;
			}
			for (int j = 0; j < m_table[i].size(); ++j) {
				if (std::find(usedColumns.begin(), usedColumns.end(), j) != usedColumns.end()) {
					continue;
				}
				if (min > m_table[i][j].top) {
					min = m_table[i][j].top;
					min_i = i;
					min_j = j;
				}
			}
		}
		if (m_a_rows[min_i] < m_b_cols[min_j]) {
			m_table[min_i][min_j].bottom = m_a_rows[min_i];
			m_table[min_i][min_j].used = true;
			usedRows.push_back(min_i);
			m_b_cols[min_j] -= m_a_rows[min_i];
			m_a_rows[min_i] -= m_a_rows[min_i];
			count++;
		}
		else if (m_a_rows[min_i] == m_b_cols[min_j]) {
			m_table[min_i][min_j].bottom = m_b_cols[min_j];
			m_table[min_i][min_j].used = true;
			usedColumns.push_back(min_j);
			usedRows.push_back(min_i);
			m_a_rows[min_i] -= m_b_cols[min_j];
			m_b_cols[min_j] -= m_b_cols[min_j];
			count++;
		}
		else {
			m_table[min_i][min_j].bottom = m_b_cols[min_j];
			m_table[min_i][min_j].used = true;
			usedColumns.push_back(min_j);
			m_a_rows[min_i] -= m_b_cols[min_j];
			m_b_cols[min_j] -= m_b_cols[min_j];
			count++;
		}
		if (usedRows.size() == m_table.size() || usedColumns.size() == m_table[0].size()) {
			foundInitial = true;
		}
	}
	if (count < m_a_rows.size() + m_b_cols.size() - 1) {
		double min = 100000.f;
		int min_i = -1;
		int min_j = -1;
		for (int i = 0; i < m_table.size(); ++i) {
			for (int j = 0; j < m_table[i].size(); ++j) {
				if (m_table[i][j].used) {
					continue;
				}
				if (min > m_table[i][j].top) {
					min = m_table[i][j].top;
					min_i = i;
					min_j = j;
				}
			}
		}
		m_table[min_i][min_j].bottom = 0;
		m_table[min_i][min_j].used = true;
	}
}

void TransportProblem::CalculatePotensials() {
	auto size_v = m_v_rows.size();
	m_v_rows.clear();
	m_v_rows.resize(size_v, Potential{ 0, false });

	auto size_u = m_u_cols.size();
	m_u_cols.clear();
	m_u_cols.resize(size_u, Potential{ 0, false });

	m_v_rows.back().Value = 0;
	m_v_rows.back().Found = true;
	std::vector<int> usedRows;
	for (int colIndex = 0; colIndex < m_u_cols.size(); ++colIndex) {
		if (m_table[m_v_rows.size() - 1][colIndex].used) {
			m_u_cols[colIndex].Value = m_table[m_v_rows.size() - 1][colIndex].top - m_v_rows.back().Value;
			m_u_cols[colIndex].Found = true;
		}
	}
	usedRows.push_back(m_v_rows.size() - 1);
	bool AllFound = false;
	while (usedRows.size() != size_v && !AllFound) {
		for (int i = 0; i < m_table.size(); ++i) {
			if (std::find(usedRows.begin(), usedRows.end(), i) != usedRows.end()) {
				continue;
			}
			int usedCells = 0;
			int usedForPotentials = 0;
			for (int j = 0; j < m_table[i].size(); ++j) {
				if ((m_v_rows[i].Found && m_u_cols[j].Found) || !m_table[i][j].used) {
					continue;
				}
				usedCells++;
				if (m_v_rows[i].Found && m_u_cols[j].Found) {
					usedForPotentials++;
				}
				if (m_v_rows[i].Found && !m_u_cols[j].Found) {
					m_u_cols[j].Value = m_table[i][j].top - m_v_rows[i].Value;
					m_u_cols[j].Found = true;
					usedForPotentials++;
				}
				if (!m_v_rows[i].Found && m_u_cols[j].Found) {
					m_v_rows[i].Value = m_table[i][j].top - m_u_cols[j].Value;
					m_v_rows[i].Found = true;
					usedForPotentials++;
				}
			}
			if (usedCells == usedForPotentials) {
				usedRows.push_back(i);
			}
		}
		int AllFoundCount = 0;
		for (auto v : m_v_rows) {
			if (v.Found) {
				AllFoundCount++;
			}
		}
		for (auto u : m_u_cols) {
			if (u.Found) {
				AllFoundCount++;
			}
		}
		if (AllFoundCount == m_v_rows.size() + m_u_cols.size()) {
			AllFound = true;
		}
	}
	for (int rowIndex = 0; rowIndex < m_v_rows.size(); ++rowIndex) {
		for (int colIndex = 0; colIndex < m_u_cols.size(); ++colIndex) {
			if (m_table[rowIndex][colIndex].used) {
				continue;
			}
			m_table[rowIndex][colIndex].bottom = m_v_rows[rowIndex].Value + m_u_cols[colIndex].Value - m_table[rowIndex][colIndex].top;
		}
	}
}