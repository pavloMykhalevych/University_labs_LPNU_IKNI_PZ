#pragma once

#include <string>
#include <vector>

#include "Cell.h"

class TransportProblem
{
private:
	void CreateProblem(const bool fromConsole = true, std::string fileName = "main.json");

	void ShowTable(const std::string& message = "");

	void FindInitialFucntion();

	void CalculatePotensials();

	void CalculateFunction();

	void Start();

	std::vector<double> m_v_rows;
	std::vector<double> m_u_cols;
	std::vector<double> m_a_rows;
	std::vector<double> m_b_cols;
	std::vector<std::vector<Cell>> m_table;
	double m_result;
};

