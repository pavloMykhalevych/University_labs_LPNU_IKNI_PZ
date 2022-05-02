#include "TransportProblem.h"

#include <iostream>
#include <algorithm>
#include <iomanip>

void TransportProblem::Start() {
	CreateProblem();
	FindInitialFucntion();
	CalculateFunction();
	std::cout << "Result function after finding supporting plan:\nF = " << m_result;
	CalculatePotensials();
	ShowTable();
}

void TransportProblem::CreateProblem(const bool fromConsole = true, std::string fileName = "main.json") {
	std::cout << "Enter number of supply locations:";
	int suplyNumber;
	std::cin >> suplyNumber;
	m_a_rows.resize(suplyNumber);
	std::cout << "Enter supplies:";
	for (int i = 0; i < suplyNumber; ++i) {
		std::cout << "A[" << i << "] = ";
		std::cin >> m_a_rows[i];
	}
	std::cout << "Enter number of demand locations:";
	int demandNumber;
	std::cin >> demandNumber;
	m_b_cols.resize(demandNumber);
	std::cout << "Enter demands:";
	for (int i = 0; i < demandNumber; ++i) {
		std::cout << "B[" << i << "] = ";
		std::cin >> m_b_cols[i];
	}
	m_table.resize(suplyNumber, std::vector<Cell>(demandNumber, Cell{0,0,false}));
	for (int i = 0; i < suplyNumber; ++i) {
		for (int j = 0; j < demandNumber; ++j) {
			std::cout << "a[" << i << "][" << j+1 <<"] = ";
			std::cin >> m_table[i][j].top;
		}
	}
	m_v_rows.resize(m_a_rows.size());
	m_u_cols.resize(m_b_cols.size());
}

void TransportProblem::ShowTable(const std::string& message) {
	std::cout << "\n" + message;
	std::cout << "\n";
	//1 row
	std::cout << std::setw(15) << std::left << "|";
	for (int i = 0; i < m_u_cols.size(); ++i) {
		std::cout << std::setw(15) << std::left << "|b[" + std::to_string(i + 1) + "] = " + std::to_string(m_u_cols[i]);
	}
	std::cout << "|";
	//other rows
	std::cout << "\n";
	for (int rowIndex = 0; rowIndex < m_v_rows.size(); ++rowIndex) {
		std::cout << std::setw(15) << std::left << "|a[" + std::to_string(rowIndex + 1) + "] = " + std::to_string(m_v_rows[rowIndex]);
		for (int colIndex = 0; colIndex < m_u_cols.size(); ++colIndex) {
			std::cout << std::setw(15) << std::left << "|" + std::to_string(m_table[rowIndex][colIndex].top);
		}
		std::cout << "|";
		std::cout << "\n";

		std::cout << std::setw(15) << std::left << "|";
		for (int colIndex = 0; colIndex < m_u_cols.size(); ++colIndex) {
			std::cout << std::setw(15) << std::left << "|" + std::to_string(m_table[rowIndex][colIndex].bottom);
		}
		std::cout << "|";
		std::cout << "\n";
	}
	std::cout << "\n";
}

void TransportProblem::CalculateFunction() {
	m_result = 0;
	for (int i = 0; i < m_table.size(); ++i) {
		for (int j = 0; j < m_table[i].size(); ++j) {
			if (m_table[i][j].used) {
				m_result += m_table[i][j].top * m_table[i][j].bottom;
			}
		}
	}
}

void TransportProblem::FindInitialFucntion() {
	std::vector<int> usedRows;
	std::vector<int> usedColumns;
	int count = 0;
	bool foundInitial = false;
	while (!foundInitial) {
		double min = 0.f;
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
		if (m_a_rows[min_i] <= m_b_cols[min_j]) {
			m_table[min_i][min_j].bottom = m_a_rows[min_i];
			m_table[min_i][min_j].used = true;
			usedRows.push_back(min_i);
			m_a_rows[min_i] -= m_a_rows[min_i];
			m_b_cols[min_j] -= m_a_rows[min_i];
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
		double min = 0.f;
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
		m_table[min_i][min_j].bottom = 0;
		m_table[min_i][min_j].used = true;
	}
}

void TransportProblem::CalculatePotensials() {

}