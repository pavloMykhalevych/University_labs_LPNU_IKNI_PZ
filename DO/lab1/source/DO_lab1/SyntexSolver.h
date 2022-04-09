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

	void ConvertToCanonical(EquationConditions& conditions);

	void ShowConditions(EquationConditions& conditions, const std::string& message = "");

	void AddAllParams(EquationConditions& conditions);

	void CreateSyntexTable();

	void ShowSyntexTable();

	void ShowSyntexTableWithDoubleMethod();

	void CalculateQ();

	bool CheckIfCanSolve();

	void RecalculateTable();

	bool FoundOptimal();

	void Solve();

	bool FoundOptimalDoubleMethod();

	void CreateTableForDoubleMethod();

	void CreateTableForDoubleMethodFromSyntex();

	void SolveWithDoubleMethod(bool fromSyntex = false);

	void CalculateQForDoubleMethod();

	void GomorySolve();

	void GomorySolveAfterInitialResult();

	bool CheckGomoryResults();

	bool SolveWithGomory();

private:
	EquationConditions m_conditions;
	EquationConditions m_conditionsDoubleMethod;

	int startParamNumber;

	std::vector<int> basisVectorIndices;

	std::vector<std::vector<double>> m_syntexTable;

	std::vector<double> m_q;

	std::vector<double> m_lastColumn;
	std::vector<double> m_lastRow;

	int m_mainColIndex = -2;
	int m_mainRowIndex = -2;

	bool m_GomorySolve = false;

	std::vector<std::pair<double, int>> m_resultsValueWithBasisVectorIndex;
};
