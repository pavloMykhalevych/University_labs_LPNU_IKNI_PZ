#pragma once

#include "SyntexSolver.h"

class HybridGame
{
public:
	void Start();

private:
	void CreateProblem(const bool fromConsole, std::string fileName);

	bool FindBoundaries();

	void SimplifyProblem();

	void CreateSymplexTables();

	void ShowResults();

	std::vector<std::vector<int>> m_table;
	std::vector<std::vector<int>> m_simplifiedTable;
	std::vector<double> m_q;
	std::vector<double> m_p;
	double m_v;
	SyntexSolver m_syntexSolver;
};

