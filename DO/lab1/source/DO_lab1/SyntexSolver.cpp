#include "SyntexSolver.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>

void SyntexSolver::Start() {
	//CreateProblem(true, "SyntexSolver_2.json");
	CreateProblem();
	Solve();
}

void SyntexSolver::CreateProblem(const bool fromFile, std::string str) {
	if (fromFile) {
		std::ifstream jsonFile(str);
		if (jsonFile.fail())
		{
			throw std::runtime_error("Ground truth was not found.\n");
		}
		nlohmann::json parsedJson = nlohmann::json::parse(jsonFile);
		m_conditions.m_problem = Equation::CreateFromFile(EquationType::Problem, parsedJson);
		int equationsNumber = parsedJson.at("Equations").at("EquationsCount").get<double>();
		for (int i = 0; i < equationsNumber; ++i) {
			m_conditions.m_equations.push_back(Equation::CreateFromFile(EquationType::Simple, parsedJson, i));
		}
		int parametersNumber = parsedJson.at("Parameters").at("Count").get<double>();
		for (int i = 0; i < parametersNumber; ++i) {
			m_conditions.m_parameters.push_back(Equation::CreateFromFile(EquationType::ParamSign, parsedJson, i));
		}
	}
	else {
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
	AddAllParams();
	ShowConditions();
	ConvertToCanonical();
	ShowConditions("\nAfter converting to canonical\n");
}

void SyntexSolver::ConvertToCanonical() {
	for (auto& equation : m_conditions.m_parameters) {
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
			m_conditions.m_removedParam.push_back(std::pair<int, double>(equation.GetCoeficients()[0].first, equation.GetB()));
			equation.SetSign(EquationSign::None);
			equation.SetB(m_conditions.m_parameters.size());
			Equation y1, y2;
			y1.SetCoeficient(m_conditions.m_parameters.size()+1, 1);
			y1.SetSign(EquationSign::GreaterThan);
			y1.SetB(0);
			y2.SetCoeficient(m_conditions.m_parameters.size()+2, 1);
			y2.SetSign(EquationSign::GreaterThan);
			y2.SetB(0);
			m_conditions.m_parameters.push_back(y1);
			m_conditions.m_parameters.push_back(y2);
			break;
		}
		}
		break;
	}
	for (auto& equation : m_conditions.m_equations) {
		auto& coeficients = equation.GetCoeficients();
		for (auto& coeficient : coeficients) {
			auto& parameter = m_conditions.m_parameters[coeficient.first - 1];
			if (parameter.GetSign() == EquationSign::None) {
				auto paramY1 = m_conditions.m_parameters[static_cast<int>(parameter.GetB())];
				auto paramY2 = m_conditions.m_parameters[static_cast<int>(parameter.GetB()) + 1];
				auto prevCoef = coeficient.second;
				coeficient = std::pair<int, double>(static_cast<int>(parameter.GetB()), prevCoef);
				auto coeficient2 = std::pair<int, double>(static_cast<int>(parameter.GetB()) + 1, -prevCoef);
				auto index = &coeficient - &coeficients[0];
				coeficients.insert(coeficients.begin() + (index + 1), coeficient2);
			}
		}
		if (equation.GetSign() == EquationSign::GreaterThan) {
			Equation y;
			y.SetCoeficient(m_conditions.m_parameters.size() + 1, 1);
			y.SetSign(EquationSign::GreaterThan);
			y.SetB(0);
			coeficients.push_back(std::pair<int, double>(m_conditions.m_parameters.size() + 1, -1));
			m_conditions.m_parameters.push_back(y);
		}
		else if (equation.GetSign() == EquationSign::LessThan) {
			Equation y;
			y.SetCoeficient(m_conditions.m_parameters.size() + 1, 1);
			y.SetSign(EquationSign::GreaterThan);
			y.SetB(0);
			coeficients.push_back(std::pair<int, double>(m_conditions.m_parameters.size() + 1, 1));
			m_conditions.m_parameters.push_back(y);
		}
		equation.SetSign(EquationSign::Equal);
	}
	auto& problemCoeficients = m_conditions.m_problem.GetCoeficients();
	for (auto& coeficient : problemCoeficients) {
		auto& parameter = m_conditions.m_parameters[coeficient.first];
		if (parameter.GetSign() == EquationSign::None) {
			auto paramY1 = m_conditions.m_parameters[static_cast<int>(parameter.GetB())];
			auto paramY2 = m_conditions.m_parameters[static_cast<int>(parameter.GetB()) + 1];
			auto prevCoef = coeficient.second;
			coeficient = std::pair<int, double>(static_cast<int>(parameter.GetB()), prevCoef);
			auto coeficient2 = std::pair<int, double>(static_cast<int>(parameter.GetB()) + 1, -prevCoef);
			auto index = &coeficient - &problemCoeficients[0];
			problemCoeficients.insert(problemCoeficients.begin() + (index + 1), coeficient2);
		}
	}
	if (m_conditions.m_problem.GetB() == 0) {
		for (auto& a : m_conditions.m_problem.GetCoeficients()) {
			a.second = -(a.second);
		}
		m_conditions.m_problem.SetB(1);
	}
	AddAllParams();
}

void SyntexSolver::AddAllParams() {
	for (auto& equation : m_conditions.m_equations) {
		auto& coeficients = equation.GetCoeficients();
		for (int i = 1; i <= m_conditions.m_parameters.size(); ++i) {
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
	auto& problemCoeficients = m_conditions.m_problem.GetCoeficients();
	for (int i = 1; i <= m_conditions.m_parameters.size(); ++i) {
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

void SyntexSolver::ShowConditions(const std::string& message) {
	std::cout << message;
	std::cout << m_conditions;
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
			m_lastColumn[j] = m_syntexTable[j][0] / m_syntexTable[j][m_mainColIndex];
			if (m_lastColumn[j] > 0 && m_lastColumn[j] < min_row) {
				min_row = m_lastColumn[j];
				min_index_row = j;
			}
		}
	}
	m_lastColumn[m_lastColumn.size() - 1] = min;
	m_mainRowIndex = min_index_row;
}

bool SyntexSolver::FoundOptimal() {
	return m_mainColIndex == -1;
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
	std::cout << std::setw(10) << std::left << "|x"
		<< std::setw(11) << std::left << "|c"
		<< std::setw(11) << std::left << "|P[0]";
	const auto& problemCoef = m_conditions.m_problem.GetCoeficients();
	for (int i = 0; i < m_conditions.m_parameters.size() - m_conditions.m_removedParam.size(); ++i) {
		std::cout << "|c[" << problemCoef[i].first << "] = ";
		std::cout << std::setw(3) << std::left << problemCoef[i].second;
	}
	std::cout << std::setw(11) << std::left << "|" << "|";
	// 2 row.
	std::cout << "\n";
	std::cout << std::setw(10) << std::left << "|"
		<< std::setw(11) << std::left << "|"
		<< std::setw(11) << std::left << "|";
	for (int i = 0; i < m_conditions.m_parameters.size() - m_conditions.m_removedParam.size(); ++i) {
		std::cout << "|P[" << problemCoef[i].first << std::setw(7) << std::left <<"]";
	}
	std::cout << std::setw(11) << std::left << "|" << "|";
	// Matrix
	for (int i = 0; i < m_syntexTable.size(); ++i) {
		std::cout << "\n";
		std::cout<< "|x[" << (basisVectorIndices[i] + 1) << std::setw(6) << std::left << "]";
		std::cout << "|" << std::setw(10) << std::left << problemCoef[basisVectorIndices[i]].second;
		for (int j = 0; j < m_syntexTable[0].size(); ++j) {
			std::cout << "|" << std::setw(10) << std::left << m_syntexTable[i][j];
		}
		if (m_lastColumn[i] < 0) {
			std::cout << "|" << std::setw(10) << std::left << "   < 0" << "|";
		}
		else {
			std::cout << "|" << std::setw(10) << std::left << m_lastColumn[i] << "|";
		}
	}
	// Q
	std::cout << "\n";
	std::cout << std::setw(10) << std::left << "|Q"
		<< std::setw(11) << std::left << "|   =";
	for (int i = 0; i < m_q.size(); ++i) {
		std::cout << "|" << std::setw(10) << std::left << m_q[i];
	}
	if (m_lastColumn[m_lastColumn.size() - 1] == 0) {
		std::cout << std::setw(11) << std::left << "|" << "|";
	}
	else {
		std::cout << "|" << std::setw(10) << std::left << m_lastColumn[m_lastColumn.size() - 1] << "|";
	}
	std::cout << "\n";
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
	}
}

std::ostream& operator<<(std::ostream& cout, EquationConditions& equationConditions) {
	cout << "\nProblem:\n";
	{
		const auto& problemCoef = equationConditions.m_problem.GetCoeficients();
		for (int i = 0; i < equationConditions.m_parameters.size() - equationConditions.m_removedParam.size(); ++i) {
			std::string sign = (problemCoef[i].second > 0) ? "+" : "";
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
			std::string sign = (equationCoef[i].second > 0) ? "+" : "";
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
			cout << "x[" << equation.GetCoeficients()[0].first << "] = "
				<< "x[" << equationConditions.m_parameters[static_cast<int>(equation.GetB())].GetCoeficients()[0].first << "] - "
				<< "x[" << equationConditions.m_parameters[static_cast<int>(equation.GetB()) + 1].GetCoeficients()[0].first << "]\n";
		}
		else if (equation.GetSign() == EquationSign::GreaterThan) {
			cout << "x[" << equation.GetCoeficients()[0].first << "] > 0\n";
		}
		else if (equation.GetSign() == EquationSign::LessThan) {
			cout << "x[" << equation.GetCoeficients()[0].first << "] < 0\n";
		}
		else if (equation.GetSign() == EquationSign::NotEqual) {
			cout << "x[" << equation.GetCoeficients()[0].first << "] <> 0\n";
		}
	}
	return cout;
}