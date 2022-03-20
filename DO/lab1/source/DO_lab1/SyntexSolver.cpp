#include "SyntexSolver.h"

#include <fstream>
#include <iostream>
#include <iomanip>

void SyntexSolver::Start() {
	CreateProblem();
	Solve();
}

void SyntexSolver::CreateProblem(const bool fromFile) {
	if (fromFile) {
		std::ifstream jsonFile("SyntexSolver.json");
		if (jsonFile.fail())
		{
			throw std::runtime_error("Ground truth was not found.\n");
		}
		nlohmann::json parsedJson = nlohmann::json::parse(jsonFile);
		m_conditions.m_problem = Equation::CreateFromFile(EquationType::Problem, parsedJson);
		int equationsNumber = parsedJson.at("Equations").at("EquationsCount").get<int>();
		for (int i = 0; i < equationsNumber; ++i) {
			m_conditions.m_equations.push_back(Equation::CreateFromFile(EquationType::Simple, parsedJson, i));
		}
		int parametersNumber = parsedJson.at("Parameters").at("Count").get<int>();
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
			m_removedParam.push_back(std::pair<int, double>(equation.GetCoeficients()[0].first, equation.GetB()));
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
				auto paramY1 = m_conditions.m_parameters[static_cast<int>(parameter.GetB()) - 1];
				auto paramY2 = m_conditions.m_parameters[static_cast<int>(parameter.GetB())];
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
			auto paramY1 = m_conditions.m_parameters[static_cast<int>(parameter.GetB()) - 1];
			auto paramY2 = m_conditions.m_parameters[static_cast<int>(parameter.GetB())];
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
			if ((j - 1) < equationCoef.size()) {
				m_syntexTable[i][j] = equationCoef[j - 1].second;
			}
			else {
				m_syntexTable[i][j] = 0;
			}
		}
	}
}

void SyntexSolver::CalculateQ() {
	m_q[0] = 0;
	double min = 0;
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
		}
	}
	for (int j = 0; j < m_syntexTable.size(); ++j) {
		if (m_syntexTable[j][1] == 0) {
			m_lastColumn[j] = -1;
		}
		else {
			m_lastColumn[j] = m_syntexTable[j][0] / m_syntexTable[j][1];
		}
	}
	m_lastColumn[m_lastColumn.size() - 1] = min;
}

void SyntexSolver::FindMainRowAndCol() {

}

void SyntexSolver::RecalculateTable() {

}

void SyntexSolver::ShowSyntexTable() {
	// 1 row.
	std::cout << "\n";
	std::cout << std::setw(10) << std::left << "|x"
		<< std::setw(11) << std::left << "|c"
		<< std::setw(11) << std::left << "|P[0]";
	const auto& problemCoef = m_conditions.m_problem.GetCoeficients();
	for (int i = 0; i < m_conditions.m_parameters.size(); ++i) {
		std::cout << "|c[" << i+1 << "] = ";
		if (i < problemCoef.size()) {
			std::cout << std::setw(3) << std::left << problemCoef[i].second;
		}
		else {
			std::cout << std::setw(3) << std::left << "0";
		}
	}
	std::cout << std::setw(11) << std::left << "|" << "|";
	// 2 row.
	std::cout << "\n";
	std::cout << std::setw(10) << std::left << "|"
		<< std::setw(11) << std::left << "|"
		<< std::setw(11) << std::left << "|";
	for (int i = 0; i < m_conditions.m_parameters.size(); ++i) {
		std::cout << "|P[" << i+1 << std::setw(7) << std::left <<"]";
	}
	std::cout << std::setw(11) << std::left << "|" << "|";
	// Matrix
	for (int i = 0; i < m_syntexTable.size(); ++i) {
		std::cout << "\n";
		std::cout<< "|x[" << (basisVectorIndices[i] + 1) << std::setw(6) << std::left << "]";
		if (basisVectorIndices[i] < problemCoef.size()) {
			std::cout << "|" << std::setw(10) << std::left << problemCoef[basisVectorIndices[i]].second;
		}
		else {
			std::cout << "|" << std::setw(10) << std::left << 0;
		}
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
}

std::ostream& operator<<(std::ostream& cout, EquationConditions& equationConditions) {
	cout << "\nProblem:\n";
	{
		const auto& problemCoef = equationConditions.m_problem.GetCoeficients();
		int index = 0;
		for (int i = 1; i <= equationConditions.m_parameters.size(); ++i) {
			std::string sign = (problemCoef[index].second > 0) ? "+" : "";
			cout << sign << problemCoef[index].second << "* x[" << i << "] ";
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
		int index = 0;
		for (int i = 1; i <= equationConditions.m_parameters.size(); ++i) {
			std::string sign = (equationCoef[index].second > 0) ? "+" : "";
			cout << sign << equationCoef[index].second << "* x[" << i << "] ";
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