#include "SyntexSolver.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>

void SyntexSolver::Start() {
	CreateProblem(true, "SyntexSolver_main_Gomori.json");
	//CreateProblem();
	if (SolveWithGomory()) {
		GomorySolve();
	}
	else {
		if (!CheckIfCanSolve()) {
			std::cout << "\nCan't solve with syntex method!\n";
			SolveWithDoubleMethod();
		}
		else {
			Solve();
			SolveWithDoubleMethod(true);
		}
	}
}

void SyntexSolver::CreateProblem(const bool fromFile, std::string str) {
	if (fromFile) {
		std::ifstream jsonFile(str);
		if (jsonFile.fail())
		{
			throw std::runtime_error("File was not found.\n");
		}
		nlohmann::json parsedJson = nlohmann::json::parse(jsonFile);
		m_GomorySolve = parsedJson.at("Integer_Numbers").get<bool>();
		m_conditions.m_problem = Equation::CreateFromFile(EquationType::Problem, parsedJson);
		int equationsNumber = parsedJson.at("Equations").at("EquationsCount").get<int>();
		for (int i = 0; i < equationsNumber; ++i) {
			m_conditions.m_equations.push_back(Equation::CreateFromFile(EquationType::Simple, parsedJson, i));
		}
		int parametersNumber = parsedJson.at("Parameters").at("Count").get<int>();
		for (int i = 0; i < parametersNumber; ++i) {
			m_conditions.m_parameters.push_back(Equation::CreateFromFile(EquationType::ParamSign, parsedJson, i));
		}
		m_resultsValueWithBasisVectorIndex.resize(m_conditions.m_parameters.size(), std::pair<double, int>(0, -1));
	}
	else {
		std::cout << "\nSolve only for integer basic parameter? (1 - yes, 0 - no) ";
		int GomorySolve;
		std::cin >> GomorySolve;
		m_GomorySolve = static_cast<bool>(GomorySolve);
		std::cout << "\nEnter the problem: ";
		m_conditions.m_problem = Equation::Create(EquationType::Problem);
		int equationsNumber = 0;
		while (equationsNumber <= 0) {
			std::cout << "\nEnter number of equations: ";
			std::cin >> equationsNumber;
			if (equationsNumber <= 0) {
				std::cout << "\nTry again)";
			}
		}
		for (int i = 0; i < equationsNumber; ++i) {
			m_conditions.m_equations.push_back(Equation::Create(EquationType::Simple));
		}
		int parametersNumber = 0;
		while (parametersNumber <= 0) {
			std::cout << "\nEnter number of parameters to set their signs: ";
			std::cin >> parametersNumber;
			if (parametersNumber <= 0) {
				std::cout << "\nTry again)";
			}
		}
		for (int i = 0; i < parametersNumber; ++i) {
			m_conditions.m_parameters.push_back(Equation::Create(EquationType::ParamSign));
		}
	}
	startParamNumber = m_conditions.m_parameters.size();
	AddAllParams(m_conditions);
	ShowConditions(m_conditions);
	ConvertToCanonical(m_conditions);
	ShowConditions(m_conditions, "\nAfter converting to canonical\n");
}

bool SyntexSolver::CheckIfCanSolve() {
	for (auto& equation : m_conditions.m_equations) {
		for (auto coef : equation.GetCoeficients()) {
			if (coef.second == 0) {
				continue;
			}
			if (coef.first <= startParamNumber - 1) {
				continue;
			}
			if (coef.second == -1) {
				for (auto& changeCoef : equation.GetCoeficients()) {
					changeCoef.second = -changeCoef.second;
				}
				equation.SetB(-(equation.GetB()));
			}
		}
		if (equation.GetB() < 0) {
			return false;
		}
	}
	return true;
}

void SyntexSolver::ConvertToCanonical(EquationConditions& conditions) {
	for (auto& equation : conditions.m_parameters) {
		switch (equation.GetSign())
		{
		case EquationSign::LessThan:
		{
			if (equation.GetSign() == EquationSign::LessThan) {
				for (auto& a : equation.GetCoeficients()) {
					a.second = -(a.second);
				}
				equation.SetSign(EquationSign::GreaterThan);
			}
			break;
		}
		case EquationSign::NotEqual:
		{
			conditions.m_removedParam.push_back(std::pair<int, double>(equation.GetCoeficients()[0].first, equation.GetB()));
			equation.SetSign(EquationSign::None);
			equation.SetB(conditions.m_parameters.size());
			Equation y1, y2;
			y1.SetCoeficient(conditions.m_parameters.size(), 1);
			y1.SetSign(EquationSign::GreaterThan);
			y1.SetB(0);
			y2.SetCoeficient(conditions.m_parameters.size()+1, 1);
			y2.SetSign(EquationSign::GreaterThan);
			y2.SetB(0);
			conditions.m_parameters.push_back(y1);
			conditions.m_parameters.push_back(y2);
			break;
		}
		}
		break;
	}
	for (auto& equation : conditions.m_equations) {
		auto& coeficients = equation.GetCoeficients();
		for (auto& coeficient : coeficients) {
			auto& parameter = conditions.m_parameters[coeficient.first - 1];
			if (parameter.GetSign() == EquationSign::None) {
				auto paramY1 = conditions.m_parameters[static_cast<int>(parameter.GetB())];
				auto paramY2 = conditions.m_parameters[static_cast<int>(parameter.GetB()) + 1];
				auto prevCoef = coeficient.second;
				coeficient = std::pair<int, double>(static_cast<int>(parameter.GetB()), prevCoef);
				auto coeficient2 = std::pair<int, double>(static_cast<int>(parameter.GetB()) + 1, -prevCoef);
				auto index = &coeficient - &coeficients[0];
				coeficients.insert(coeficients.begin() + (index + 1), coeficient2);
			}
		}
		if (equation.GetSign() == EquationSign::GreaterThan) {
			Equation y;
			y.SetCoeficient(conditions.m_parameters.size(), 1);
			y.SetSign(EquationSign::GreaterThan);
			y.SetB(0);
			coeficients.push_back(std::pair<int, double>(conditions.m_parameters.size() + 1, -1));
			conditions.m_parameters.push_back(y);
		}
		else if (equation.GetSign() == EquationSign::LessThan) {
			Equation y;
			y.SetCoeficient(conditions.m_parameters.size(), 1);
			y.SetSign(EquationSign::GreaterThan);
			y.SetB(0);
			coeficients.push_back(std::pair<int, double>(conditions.m_parameters.size() + 1, 1));
			conditions.m_parameters.push_back(y);
		}
		equation.SetSign(EquationSign::Equal);
	}
	auto& problemCoeficients = conditions.m_problem.GetCoeficients();
	for (auto& coeficient : problemCoeficients) {
		auto& parameter = conditions.m_parameters[coeficient.first];
		if (parameter.GetSign() == EquationSign::None) {
			auto paramY1 = conditions.m_parameters[static_cast<int>(parameter.GetB())];
			auto paramY2 = conditions.m_parameters[static_cast<int>(parameter.GetB()) + 1];
			auto prevCoef = coeficient.second;
			coeficient = std::pair<int, double>(static_cast<int>(parameter.GetB()), prevCoef);
			auto coeficient2 = std::pair<int, double>(static_cast<int>(parameter.GetB()) + 1, -prevCoef);
			auto index = &coeficient - &problemCoeficients[0];
			problemCoeficients.insert(problemCoeficients.begin() + (index + 1), coeficient2);
		}
	}
	if (conditions.m_problem.GetB() == 0) {
		for (auto& a : conditions.m_problem.GetCoeficients()) {
			a.second = -(a.second);
		}
		conditions.m_problem.SetB(1);
	}
	AddAllParams(conditions);
}

void SyntexSolver::AddAllParams(EquationConditions& conditions) {
	for (auto& equation : conditions.m_equations) {
		auto& coeficients = equation.GetCoeficients();
		for (int i = 1; i <= conditions.m_parameters.size(); ++i) {
			if (i - 1 >= coeficients.size()) {
				coeficients.push_back(std::pair<int, double>(i, 0));
			}
			else if (coeficients[i-1].first < i) {
				auto index = &coeficients[i - 1] - &coeficients[0];
				coeficients.insert(coeficients.begin() + (index+1), std::pair<int, double>(i, 0));
			}
			else if (coeficients[i - 1].first > i) {
				auto index = &coeficients[i - 1] - &coeficients[0];
				coeficients.insert(coeficients.begin() + (index), std::pair<int, double>(i, 0));
			}
		}
	}
	auto& problemCoeficients = conditions.m_problem.GetCoeficients();
	for (int i = 1; i <= conditions.m_parameters.size(); ++i) {
		if (i - 1 >= problemCoeficients.size()) {
			problemCoeficients.push_back(std::pair<int, double>(i, 0));
		}
		else if (problemCoeficients[i - 1].first < i) {
			auto index = &problemCoeficients[i - 1] - &problemCoeficients[0];
			problemCoeficients.insert(problemCoeficients.begin() + (index + 1), std::pair<int, double>(i, 0));
		}
		else if (problemCoeficients[i - 1].first > i) {
			auto index = &problemCoeficients[i - 1] - &problemCoeficients[0];
			problemCoeficients.insert(problemCoeficients.begin() + (index), std::pair<int, double>(i, 0));
		}
	}
}

void SyntexSolver::ShowConditions(EquationConditions& conditions, const std::string& message) {
	std::cout << message;
	std::cout << conditions;
}

void SyntexSolver::CreateSyntexTable() {
	basisVectorIndices.resize(m_conditions.m_parameters.size() - startParamNumber, 0);
	std::iota(basisVectorIndices.begin(), basisVectorIndices.end(), startParamNumber);
	m_syntexTable.resize(basisVectorIndices.size(), std::vector<double>(m_conditions.m_parameters.size() + 1, 0));
	m_q.resize(m_conditions.m_parameters.size() + 1, 0);
	m_lastColumn.resize(basisVectorIndices.size() + 1, 0);
	for (int i = 0; i < m_syntexTable.size(); ++i) {
		const auto equationCoef = m_conditions.m_equations[i].GetCoeficients();
		m_syntexTable[i][0] = m_conditions.m_equations[i].GetB();
		for (int j = 1; j < m_syntexTable[0].size(); ++j) {
			m_syntexTable[i][j] = equationCoef[j - 1].second;
		}
	}
}

void SyntexSolver::CalculateQ() {
	for (int j = 0; j < m_syntexTable[0].size(); ++j) {
		m_q[j] = 0;
	}
	double min = 0;
	int min_index = -1;
	double min_row = std::numeric_limits<double>::max();
	int min_index_row = -1;
	const auto& problemCoef = m_conditions.m_problem.GetCoeficients();
	for (int j = 0; j < m_syntexTable.size(); ++j) {
		m_q[0] += m_syntexTable[j][0] * problemCoef[basisVectorIndices[j]].second;
	}
	for (int i = 1; i < m_syntexTable[0].size(); ++i) {
		for (int j = 0; j < m_syntexTable.size(); ++j) {
			m_q[i] += (m_syntexTable[j][i] * problemCoef[basisVectorIndices[j]].second);
		}
		m_q[i] -= problemCoef[i - 1].second;
		if (m_q[i] < 0 && m_q[i] < min) {
			min = m_q[i];
			min_index = i;
		}
	}
	m_mainColIndex = min_index;
	if (m_mainColIndex == -1) {
		for (int j = 0; j < m_syntexTable.size(); ++j) {
			m_lastColumn[j] = -1;
		}
		return;
	}
	for (int j = 0; j < m_syntexTable.size(); ++j) {
		if (m_syntexTable[j][m_mainColIndex] == 0) {
			m_lastColumn[j] = -1;
		}
		else {
			if (m_syntexTable[j][m_mainColIndex] < 0) {
				m_lastColumn[j] = -1;
			}
			else {
				m_lastColumn[j] = m_syntexTable[j][0] / m_syntexTable[j][m_mainColIndex];
				if (m_lastColumn[j] >= 0 && m_lastColumn[j] < min_row) {
					min_row = m_lastColumn[j];
					min_index_row = j;
				}
			}
		}
	}
	m_lastColumn[m_lastColumn.size() - 1] = min;
	m_mainRowIndex = min_index_row;
}

bool SyntexSolver::FoundOptimal() {
	return m_mainColIndex == -1;
}

bool SyntexSolver::FoundOptimalDoubleMethod() {
	return m_mainRowIndex == -1;
}

void SyntexSolver::RecalculateTable() {
	basisVectorIndices[m_mainRowIndex] = m_mainColIndex - 1;
	// Perpendiculars.
	for (int i = 0; i < m_syntexTable.size(); ++i) {
		if (i == m_mainRowIndex) {
			continue;
		}
		for (int j = 0; j < m_syntexTable[0].size(); ++j) {
			if (j == m_mainColIndex) {
				continue;
			}
			m_syntexTable[i][j]
				-= ((m_syntexTable[i][m_mainColIndex]* m_syntexTable[m_mainRowIndex][j]) / m_syntexTable[m_mainRowIndex][m_mainColIndex]);
		}
	}
	for (int j = 0; j < m_syntexTable[0].size(); ++j) {
		if (j == m_mainColIndex) {
			continue;
		}
		m_syntexTable[m_mainRowIndex][j] /= m_syntexTable[m_mainRowIndex][m_mainColIndex];
	}
	for (int i = 0; i < m_syntexTable.size(); ++i) {
		if (i == m_mainRowIndex) {
			m_syntexTable[i][m_mainColIndex] = 1;
			continue;
		}
		m_syntexTable[i][m_mainColIndex] = 0;
	}
}

void SyntexSolver::ShowSyntexTable() {
	// 1 row.
	std::cout << "\n";
	std::cout << std::setw(16) << std::left << "|x"
		<< std::setw(17) << std::left << "|c"
		<< std::setw(17) << std::left << "|P[0]";
	const auto& problemCoef = m_conditions.m_problem.GetCoeficients();
	for (int i = 0; i < m_conditions.m_parameters.size() - m_conditions.m_removedParam.size(); ++i) {
		std::cout << "|c[" << problemCoef[i].first << "] = ";
		std::cout << std::setw(9) << std::left << problemCoef[i].second;
	}
	std::cout << std::setw(17) << std::left << "|" << "|";
	// 2 row.
	std::cout << "\n";
	std::cout << std::setw(16) << std::left << "|"
		<< std::setw(17) << std::left << "|"
		<< std::setw(17) << std::left << "|";
	for (int i = 0; i < m_conditions.m_parameters.size() - m_conditions.m_removedParam.size(); ++i) {
		std::cout << "|P[" << problemCoef[i].first << std::setw(13) << std::left <<"]";
	}
	std::cout << std::setw(17) << std::left << "|" << "|";
	// Matrix
	for (int i = 0; i < m_syntexTable.size(); ++i) {
		std::cout << "\n";
		std::cout<< "|x[" << (basisVectorIndices[i] + 1) << std::setw(12) << std::left << "]";
		std::cout << "|" << std::setw(16) << std::left << problemCoef[basisVectorIndices[i]].second;
		for (int j = 0; j < m_syntexTable[0].size(); ++j) {
			std::cout << "|" << std::setw(16) << std::left << m_syntexTable[i][j];
		}
		if (m_lastColumn[i] < 0) {
			std::cout << "|" << std::setw(16) << std::left << "   < 0" << "|";
		}
		else {
			std::cout << "|" << std::setw(16) << std::left << m_lastColumn[i] << "|";
		}
	}
	// Q
	std::cout << "\n";
	std::cout << std::setw(16) << std::left << "|Q"
		<< std::setw(17) << std::left << "|   =";
	for (int i = 0; i < m_q.size(); ++i) {
		std::cout << "|" << std::setw(16) << std::left << m_q[i];
	}
	if (m_lastColumn[m_lastColumn.size() - 1] == 0) {
		std::cout << std::setw(17) << std::left << "|" << "|";
	}
	else {
		std::cout << "|" << std::setw(16) << std::left << m_lastColumn[m_lastColumn.size() - 1] << "|";
	}
	std::cout << "\n";
}

void SyntexSolver::ShowSyntexTableWithDoubleMethod() {
	// 1 row.
	std::cout << "\n";
	std::cout << std::setw(16) << std::left << "|x"
		<< std::setw(17) << std::left << "|c"
		<< std::setw(17) << std::left << "|P[0]";
	const auto& problemCoef = m_conditionsDoubleMethod.m_problem.GetCoeficients();
	for (int i = 0; i < m_conditionsDoubleMethod.m_parameters.size() - m_conditionsDoubleMethod.m_removedParam.size(); ++i) {
		std::cout << "|c[" << problemCoef[i].first << "] = ";
		std::cout << std::setw(9) << std::left << problemCoef[i].second;
	}
	std::cout << "|";
	// 2 row.
	std::cout << "\n";
	std::cout << std::setw(16) << std::left << "|"
		<< std::setw(17) << std::left << "|"
		<< std::setw(17) << std::left << "|";
	for (int i = 0; i < m_conditionsDoubleMethod.m_parameters.size() - m_conditionsDoubleMethod.m_removedParam.size(); ++i) {
		std::cout << "|P[" << problemCoef[i].first << std::setw(13) << std::left << "]";
	}

	std::cout << "|";
	// Matrix
	for (int i = 0; i < m_syntexTable.size(); ++i) {
		std::cout << "\n";
		std::cout << "|x[" << (basisVectorIndices[i] + 1) << std::setw(12) << std::left << "]";
		std::cout << "|" << std::setw(16) << std::left << problemCoef[basisVectorIndices[i]].second;
		for (int j = 0; j < m_syntexTable[0].size(); ++j) {
			std::cout << "|" << std::setw(16) << std::left << m_syntexTable[i][j];
		}
		std::cout << "|";
	}
	// Q
	std::cout << "\n";
	std::cout << std::setw(16) << std::left << "|Q"
		<< std::setw(17) << std::left << "|   =";
	for (int i = 0; i < m_q.size(); ++i) {
		std::cout << "|" << std::setw(16) << std::left << m_q[i];
	}
	std::cout << "|";
	// Last row
	std::cout << "\n";
	std::cout << std::setw(16) << std::left << "|"
		<< std::setw(17) << std::left << "|"
		<< std::setw(17) << std::left << "|";
	for (int i = 0; i < m_lastRow.size(); ++i) {
		if (m_lastRow[i] < 0) {
			std::cout << std::setw(17) << std::left << "|";
		}
		else {
			std::cout << "|" << std::setw(16) << std::left << m_lastRow[i];
		}
	}
	std::cout << "|\n";
}

void SyntexSolver::Solve() {
	CreateSyntexTable();
	CalculateQ();
	ShowSyntexTable();
	while (!FoundOptimal()) {
		RecalculateTable();
		CalculateQ();
		ShowSyntexTable();
	}
	std::cout << "\n Optimal parameters and value:\n";
	std::cout << "Q = " << m_q[0] << "\n";
	for (int i = 0; i < m_conditions.m_parameters.size(); ++i) {
		auto basisVectorIndicesIterator =
			std::find(basisVectorIndices.begin(), basisVectorIndices.end(), m_conditions.m_parameters[i].GetCoeficients()[0].first);
		if (basisVectorIndicesIterator != basisVectorIndices.end()) {
			int index = std::distance(basisVectorIndices.begin(), basisVectorIndicesIterator);
			if (m_conditions.m_problem.GetCoeficients()[*basisVectorIndicesIterator].second != 0) {
				std::cout << "x[" << m_conditions.m_parameters[i].GetCoeficients()[0].first + 1 << "] = " << m_syntexTable[index][0] << "\n";
			}
		}
		else {
			std::cout << "x[" << m_conditions.m_parameters[i].GetCoeficients()[0].first + 1 << "] = 0" << "\n";
		}
	}
}

std::ostream& operator<<(std::ostream& cout, EquationConditions& equationConditions) {
	cout << "\nProblem:\n";
	{
		const auto& problemCoef = equationConditions.m_problem.GetCoeficients();
		for (int i = 0; i < equationConditions.m_parameters.size() - equationConditions.m_removedParam.size(); ++i) {
			std::string sign = (problemCoef[i].second >= 0) ? "+" : "";
			cout << sign << problemCoef[i].second << "* x[" << problemCoef[i].first << "] ";
		}
		std::string minMaxStr;
		if (equationConditions.m_problem.GetB() == 0)
		{
			minMaxStr = "Min";
		}
		else {
			minMaxStr = "Max";
		}
		cout << "==> " << minMaxStr << "\n";
	}
	cout << "\nEquations:\n";
	for (auto& equation : equationConditions.m_equations) {
		const auto& equationCoef = equation.GetCoeficients();
		for (int i = 0; i < equationConditions.m_parameters.size() - equationConditions.m_removedParam.size(); ++i) {
			std::string sign = (equationCoef[i].second >= 0) ? "+" : "";
			cout << sign << equationCoef[i].second << "* x[" << equationCoef[i].first << "] ";
		}
		if (equation.GetSign() == EquationSign::GreaterThan) {
			cout << "> ";
		}
		else if (equation.GetSign() == EquationSign::LessThan) {
			cout << "< ";
		}
		else if (equation.GetSign() == EquationSign::Equal) {
			cout << "= ";
		}
		cout << equation.GetB() << "\n";
	}
	cout << "\nParameters:\n";
	for (auto& equation : equationConditions.m_parameters) {
		if (equation.GetSign() == EquationSign::None) {
			cout << "x[" << equation.GetCoeficients()[0].first + 1 << "] = "
				<< "x[" << equationConditions.m_parameters[static_cast<int>(equation.GetB())].GetCoeficients()[0].first + 1 << "] - "
				<< "x[" << equationConditions.m_parameters[static_cast<int>(equation.GetB()) + 1].GetCoeficients()[0].first + 1 << "]\n";
		}
		else if (equation.GetSign() == EquationSign::GreaterThan) {
			cout << "x[" << equation.GetCoeficients()[0].first + 1 << "] > 0\n";
		}
		else if (equation.GetSign() == EquationSign::LessThan) {
			cout << "x[" << equation.GetCoeficients()[0].first + 1 << "] < 0\n";
		}
		else if (equation.GetSign() == EquationSign::NotEqual) {
			cout << "x[" << equation.GetCoeficients()[0].first + 1 << "] <> 0\n";
		}
	}
	return cout;
}

void SyntexSolver::CreateTableForDoubleMethodFromSyntex() {
	auto paramSize = m_conditions.m_equations.size();
	startParamNumber = paramSize;
	auto coefSize = m_conditions.m_equations[0].GetCoeficients().size();
	auto prevProblemCoefs = m_conditions.m_problem.GetCoeficients();
	std::vector<std::pair<int, double>> problemCoefs;
	std::vector<std::vector<std::pair<int, double>>> equationsCoefs(coefSize);
	for (int i = 0; i < paramSize; ++i) {
		auto coefs = m_conditions.m_equations[i].GetCoeficients();
		for (int j = 0; j < coefSize; ++j) {
			equationsCoefs[j].push_back({i+1, coefs[j].second});
		}
		problemCoefs.push_back({ i + 1, m_conditions.m_equations[i].GetB() });
		m_conditionsDoubleMethod.m_parameters.push_back(Equation::Create({ {i, 1} }, EquationSign::GreaterThan, 0));
	}
	for (int i = 0; i < coefSize; ++i) {
		int count1 = 0;
		int count0 = 0;
		for (int j = 0; j < equationsCoefs[i].size(); ++j) {
			if (equationsCoefs[i][j].second == 0) {
				count0++;
			}
			else if (equationsCoefs[i][j].second == 1) {
				count1++;
			}
		}
		if (!(((count1 + count0) == equationsCoefs[i].size()) && (prevProblemCoefs[i].second == 0))) {
			m_conditionsDoubleMethod.m_equations.push_back(Equation::Create(equationsCoefs[i], EquationSign::GreaterThan, prevProblemCoefs[i].second));
		}
	}
	m_conditionsDoubleMethod.m_problem = Equation::Create(problemCoefs, EquationSign::None, 0);
	AddAllParams(m_conditionsDoubleMethod);
	ShowConditions(m_conditionsDoubleMethod, "\nSolve with double method.\n");
	ConvertToCanonical(m_conditionsDoubleMethod);
	for (auto& equation : m_conditionsDoubleMethod.m_equations) {
		for (auto coef : equation.GetCoeficients()) {
			if (coef.second == 0) {
				continue;
			}
			if (coef.first <= paramSize - 1) {
				continue;
			}
			if (coef.second == -1) {
				for (auto& changeCoef : equation.GetCoeficients()) {
					changeCoef.second = -changeCoef.second;
				}
				equation.SetB(-(equation.GetB()));
			}
		}
	}
	basisVectorIndices.resize(m_conditionsDoubleMethod.m_parameters.size() - paramSize, 0);
	std::iota(basisVectorIndices.begin(), basisVectorIndices.end(), paramSize);
	m_syntexTable.resize(basisVectorIndices.size(), std::vector<double>(m_conditionsDoubleMethod.m_parameters.size() + 1, 0));
	m_q.resize(m_conditionsDoubleMethod.m_parameters.size() + 1, 0);
	m_lastRow.resize(m_q.size() - 1, 0);
	for (int i = 0; i < m_syntexTable.size(); ++i) {
		const auto equationCoef = m_conditionsDoubleMethod.m_equations[i].GetCoeficients();
		m_syntexTable[i][0] = m_conditionsDoubleMethod.m_equations[i].GetB();
		for (int j = 1; j < m_syntexTable[0].size(); ++j) {
			m_syntexTable[i][j] = equationCoef[j - 1].second;
		}
	}
	ShowConditions(m_conditionsDoubleMethod, "\nAfter converting to canonical\n");
}

void SyntexSolver::CreateTableForDoubleMethod() {
	m_conditionsDoubleMethod = m_conditions;
	for (auto& equation : m_conditionsDoubleMethod.m_equations) {
		for (auto coef : equation.GetCoeficients()) {
			if (coef.second == 0) {
				continue;
			}
			if (coef.first <= startParamNumber - 1) {
				continue;
			}
			if (coef.second == -1) {
				for (auto& changeCoef : equation.GetCoeficients()) {
					changeCoef.second = -changeCoef.second;
				}
				equation.SetB(-(equation.GetB()));
			}
		}
	}
	basisVectorIndices.resize(m_conditionsDoubleMethod.m_parameters.size() - startParamNumber, 0);
	std::iota(basisVectorIndices.begin(), basisVectorIndices.end(), startParamNumber);
	m_syntexTable.resize(basisVectorIndices.size(), std::vector<double>(m_conditionsDoubleMethod.m_parameters.size() + 1, 0));
	m_q.resize(m_conditionsDoubleMethod.m_parameters.size() + 1, 0);
	m_lastRow.resize(m_q.size() - 1, 0);
	for (int i = 0; i < m_syntexTable.size(); ++i) {
		const auto equationCoef = m_conditionsDoubleMethod.m_equations[i].GetCoeficients();
		m_syntexTable[i][0] = m_conditionsDoubleMethod.m_equations[i].GetB();
		for (int j = 1; j < m_syntexTable[0].size(); ++j) {
			m_syntexTable[i][j] = equationCoef[j - 1].second;
		}
	}
	ShowConditions(m_conditionsDoubleMethod, "\nSolve with double method.\n");
}

void SyntexSolver::SolveWithDoubleMethod(bool fromSyntex) {
	if (fromSyntex) {
		CreateTableForDoubleMethodFromSyntex();
	}
	else {
		CreateTableForDoubleMethod();
	}
	CalculateQForDoubleMethod();
	ShowSyntexTableWithDoubleMethod();
	while (!FoundOptimalDoubleMethod()) {
		RecalculateTable();
		CalculateQForDoubleMethod();
		ShowSyntexTableWithDoubleMethod();
	}
	std::cout << "\n Optimal parameters and value:\n";
	std::cout << "Q = " << -m_q[0] << "\n";
	for (int i = 0; i < m_conditionsDoubleMethod.m_parameters.size() - startParamNumber + 1; ++i) {
		auto basisVectorIndicesIterator =
			std::find(basisVectorIndices.begin(), basisVectorIndices.end(), m_conditionsDoubleMethod.m_parameters[i].GetCoeficients()[0].first);
		if (basisVectorIndicesIterator != basisVectorIndices.end()) {
			int index = std::distance(basisVectorIndices.begin(), basisVectorIndicesIterator);
			if (m_conditionsDoubleMethod.m_problem.GetCoeficients()[*basisVectorIndicesIterator].second != 0) {
				std::cout << "x[" << m_conditionsDoubleMethod.m_parameters[i].GetCoeficients()[0].first + 1 << "] = " << m_syntexTable[index][0] << "\n";
			}
			else {
				std::cout << "x[" << m_conditionsDoubleMethod.m_parameters[i].GetCoeficients()[0].first + 1 << "] = 0" << "\n";
			}
		}
		else {
			std::cout << "x[" << m_conditionsDoubleMethod.m_parameters[i].GetCoeficients()[0].first + 1 << "] = 0" << "\n";
		}
	}
}

void SyntexSolver::CalculateQForDoubleMethod() {
	for (int j = 0; j < m_syntexTable[0].size(); ++j) {
		m_q[j] = 0;
	}
	double min_row = 0;
	int min_index_row = -1;
	double min_col = std::numeric_limits<double>::max();
	int min_index_col = -1;
	const auto& problemCoef = m_conditionsDoubleMethod.m_problem.GetCoeficients();
	for (int j = 0; j < m_syntexTable.size(); ++j) {
		m_q[0] += m_syntexTable[j][0] * problemCoef[basisVectorIndices[j]].second;
	}
	for (int i = 1; i < m_syntexTable[0].size(); ++i) {
		for (int j = 0; j < m_syntexTable.size(); ++j) {
			m_q[i] += (m_syntexTable[j][i] * problemCoef[basisVectorIndices[j]].second);
		}
		m_q[i] -= problemCoef[i - 1].second;
		for (int n = 0; n < m_syntexTable.size(); ++n) {
			if (m_syntexTable[n][0] < 0 && m_syntexTable[n][0] < min_row) {
				min_row = m_syntexTable[n][0];
				min_index_row = n;
			}
		}

	}
	m_mainRowIndex = min_index_row;
	if (m_mainRowIndex == -1) {
		return;
	}
	for (int j = 1; j < m_q.size(); ++j) {
		if (m_q[j] < 0) {
			m_mainRowIndex = -1;
			return;
		}
	}
	for (int j = 1; j < m_q.size(); ++j) {
		if (m_syntexTable[m_mainRowIndex][j] >= 0) {
			continue;
		}
		else {
			auto delta = (-m_q[j]) / m_syntexTable[m_mainRowIndex][j];
			m_lastRow[j - 1] = delta;
			if (delta < min_col) {
				min_col = delta;
				min_index_col = j;
			}
		}
	}
	m_mainColIndex = min_index_col;
}

bool SyntexSolver::SolveWithGomory() {
	return m_GomorySolve;
}

void SyntexSolver::GomorySolve() {
	if (!CheckIfCanSolve()) {
		std::cout << "\nCan't solve start problem with syntex method!\n";
		SolveWithDoubleMethod();
		m_conditions = m_conditionsDoubleMethod;
	}
	else {
		Solve();
	}
	GomorySolveAfterInitialResult();
}

bool SyntexSolver::CheckGomoryResults() {
	int isIntegerCount = 0;
	for (int i = 0; i < startParamNumber; ++i) {
		auto basisVectorIndicesIterator =
			std::find(basisVectorIndices.begin(), basisVectorIndices.end(), m_conditions.m_parameters[i].GetCoeficients()[0].first);
		if (basisVectorIndicesIterator != basisVectorIndices.end()) {
			int index = std::distance(basisVectorIndices.begin(), basisVectorIndicesIterator);
			if ((m_syntexTable[index][0] - static_cast<int>(m_syntexTable[index][0])) > 0.05) {
				std::cout << "x[" << m_conditions.m_parameters[i].GetCoeficients()[0].first + 1 << "] is not integer\n";
			}
			else {
				m_syntexTable[index][0] = static_cast<int>(m_syntexTable[index][0]);
				++isIntegerCount;
			}
			m_resultsValueWithBasisVectorIndex[i] = std::pair<double, int>(m_syntexTable[index][0], index);
		}
	}
	if (isIntegerCount == startParamNumber) {
		return false;
	}
	return true;
}

void SyntexSolver::GomorySolveAfterInitialResult()
{
	while (CheckGomoryResults()) {
		std::cout << "\nResult not integer. Next iteration: \n";

		double maxValue = 0;
		int maxIndex = -1;
		for (int i = 0; i < m_resultsValueWithBasisVectorIndex.size(); ++i) {
			double fractionPart;
			if (m_resultsValueWithBasisVectorIndex[i].first >= 0) {
				fractionPart = m_resultsValueWithBasisVectorIndex[i].first - static_cast<int>(m_resultsValueWithBasisVectorIndex[i].first);
			}
			else {
				fractionPart = m_resultsValueWithBasisVectorIndex[i].first - static_cast<int>(m_resultsValueWithBasisVectorIndex[i].first - 1);
			}

			if (fractionPart > maxValue) {
				maxValue = fractionPart;
				maxIndex = m_resultsValueWithBasisVectorIndex[i].second;
			}
		}
		if (maxValue == 0 || maxIndex == -1) {
			std::cout << "Error! Fraction part = 0.";
			return;
		}
		std::vector<std::pair<int, double>> coef;
		for (int col = 1; col < m_syntexTable[0].size(); ++col) {
			if (col <= startParamNumber) {
				double fractionPart;
				if (m_syntexTable[maxIndex][col] >= 0) {
					fractionPart = m_syntexTable[maxIndex][col] - static_cast<int>(m_syntexTable[maxIndex][col]);
				}
				else {
					fractionPart = m_syntexTable[maxIndex][col] - static_cast<int>(m_syntexTable[maxIndex][col] - 1);
				}
				if (fractionPart <= maxValue) {
					coef.push_back(std::pair<int, double>(col, -fractionPart * 1 / maxValue));
				}
				else {
					double a = (maxValue / (1 - maxValue)) * (1 - fractionPart);
					coef.push_back(std::pair<int, double>(col, -a * 1 / maxValue));
				}
			}
			else {
				if (m_syntexTable[maxIndex][col] >= 0) {
					coef.push_back(std::pair<int, double>(col, -m_syntexTable[maxIndex][col] * 1 / maxValue));
				}
				else {
					double a = (maxValue / (1 - maxValue)) * abs(m_syntexTable[maxIndex][col]);
					coef.push_back(std::pair<int, double>(col, -a * 1 / maxValue));
				}
			}
		}
		coef.push_back(std::pair<int, double>(m_syntexTable[0].size(), 1 * 1 / maxValue));
		auto newEquation = Equation::Create(coef, EquationSign::Equal, -maxValue * 1 / maxValue);
		m_conditions.m_equations.push_back(newEquation);
		m_conditions.m_parameters.push_back(Equation::Create(std::vector<std::pair<int, double>>(1, std::pair<int, double>(m_syntexTable[0].size() - 1, 1)), EquationSign::GreaterThan, 0));
		AddAllParams(m_conditions);
		ShowConditions(m_conditions, "\nAfter adding new equation\n");

		m_q.push_back(0);
		m_lastColumn.push_back(0);
		m_lastRow.resize(m_q.size() - 1, 0);
		basisVectorIndices.push_back(m_syntexTable[0].size() - 1);

		for (int i = 0; i < m_syntexTable.size(); ++i) {
			m_syntexTable[i].push_back(0);
		}

		std::vector<double> addedRow;
		addedRow.push_back(newEquation.GetB());
		for (int i = 0; i < coef.size(); ++i) {
			addedRow.push_back(coef[i].second);
		}
		m_syntexTable.push_back(addedRow);

		m_conditionsDoubleMethod = m_conditions;

		CalculateQForDoubleMethod();
		ShowSyntexTableWithDoubleMethod();
		while (!FoundOptimalDoubleMethod()) {
			RecalculateTable();
			CalculateQForDoubleMethod();
			ShowSyntexTableWithDoubleMethod();
		}
		std::cout << "\n Optimal parameters and value:\n";
		std::cout << "Q = " << -m_q[0] << "\n";
		for (int i = 0; i < m_conditionsDoubleMethod.m_parameters.size(); ++i) {
			auto basisVectorIndicesIterator =
				std::find(basisVectorIndices.begin(), basisVectorIndices.end(), m_conditionsDoubleMethod.m_parameters[i].GetCoeficients()[0].first);
			if (basisVectorIndicesIterator != basisVectorIndices.end()) {
				int index = std::distance(basisVectorIndices.begin(), basisVectorIndicesIterator);
				if (m_conditionsDoubleMethod.m_problem.GetCoeficients()[*basisVectorIndicesIterator].second != 0) {
					std::cout << "x[" << m_conditionsDoubleMethod.m_parameters[i].GetCoeficients()[0].first + 1 << "] = " << m_syntexTable[index][0] << "\n";
				}
				else {
					std::cout << "x[" << m_conditionsDoubleMethod.m_parameters[i].GetCoeficients()[0].first + 1 << "] = 0" << "\n";
				}
			}
			else {
				std::cout << "x[" << m_conditionsDoubleMethod.m_parameters[i].GetCoeficients()[0].first + 1 << "] = 0" << "\n";
			}
		}
	}
	std::cout << "\n\nResults: \nQ = " << (int)m_q[0] << ";\n";
	for (int i = 0; i < m_resultsValueWithBasisVectorIndex.size(); ++i) {
		std::cout << "x[" << i+1 << "] = " << m_resultsValueWithBasisVectorIndex[i].first << ";\n";
	}
	std::cout << "\nEnd!!";
}
