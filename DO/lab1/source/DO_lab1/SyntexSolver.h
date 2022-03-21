#pragma once

#include "Equation.h"

#include <vector>

struct EquationConditions {
	friend std::ostream& operator<<(std::ostream& cout, EquationConditions& equation);

	std::vector<Equation> m_equations;
	std::vector<Equation> m_parameters;
	std::vector<std::pair<int, double>> m_removedParam;
	Equation m_problem;
};

class SyntexSolver
{
public:
	void Start();

private:
	void CreateProblem(const bool fromFile = true, std::string str = "SyntexSolver_main.json");

	void ConvertToCanonical();

	void ShowConditions(const std::string& message = "");

	void AddAllParams();

	void CreateSyntexTable();

	void ShowSyntexTable();

	void CalculateQ();

	void RecalculateTable();

	bool FoundOptimal();

	void Solve();

private:
	EquationConditions m_conditions;

	int startParamNumber;

	std::vector<int> basisVectorIndices;

	std::vector<std::vector<double>> m_syntexTable;

	std::vector<double> m_q;

	std::vector<double> m_lastColumn;

	int m_mainColIndex = -2;
	int m_mainRowIndex = -2;
};
