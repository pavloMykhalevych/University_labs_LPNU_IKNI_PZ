#pragma once

#include <string>
#include <vector>

#include "Cell.h"
#include "LoopCellInfo.h"
#include "Potential.h"

class TransportProblem
{
public:
	void Start();

private:
	bool IsDegenerate();

	void CreateProblem(const bool fromConsole = false, std::string fileName = "main.json");

	void ShowTable(const std::string& message = "");

	void FindInitialFucntion();

	void CalculatePotensials();

	void CalculateFunction(std::string mes = "");

	bool FindLoopAndRecalculate();

	std::pair<bool, std::vector<LoopCellInfo>> FindNextElementInLoop(const std::vector<LoopCellInfo>& path, bool horizontal);

	std::vector<LoopCellInfo> FindNeigbors(LoopCellInfo loopCellInfo, bool horizontal);

	std::vector<Potential> m_v_rows;
	std::vector<Potential> m_u_cols;
	std::vector<double> m_a_rows;
	std::vector<double> m_b_cols;
	std::vector<std::vector<Cell>> m_table;
	double m_result;
};

