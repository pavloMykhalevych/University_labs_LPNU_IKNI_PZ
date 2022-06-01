#include "Equation.h"

#include <iostream>
#include <fstream>
#include <string>

std::vector<std::pair<int, double>>& Equation::GetCoeficients() {
	return m_a;
}

void Equation::SetCoeficient(const int paramIndex, const double a) {
	m_a.push_back(std::pair<int, double>(paramIndex, a));
}

void Equation::SetCoeficient(const int index, const int paramIndex, const double a) {
	m_a[index] = (std::pair<int, double>(paramIndex, a));
}

double& Equation::GetB() {
	return m_b;
}

void Equation::SetB(const double b) {
	m_b = b;
}

const EquationSign& Equation::GetSign() const {
	return m_sign;
}

void Equation::SetSign(const EquationSign& sign) {
	m_sign = sign;
}

const EquationType& Equation::GetType() const {
	return m_type;
}

void Equation::SetType(const EquationType& type) {
	m_type = type;
}

Equation Equation::Create(const EquationType& type) {
	Equation equation;
	equation.SetType(type);
	switch (type)
	{
	case EquationType::Simple:
	{
		std::cout << "\nEnter parameters number : ";
		double paramCount;
		std::cin >> paramCount;
		for (auto i = 0; i < paramCount; ++i) {
			int index;
			std::cout << "\nEnter param index : ";
			std::cin >> index;
			std::cout << "\nEnter coeficient near x[" << index << "] : ";
			double a;
			std::cin >> a;
			equation.SetCoeficient(index, a);
		}
		EquationSign sign = EquationSign::None;
		while (sign == EquationSign::None) {
			std::cout << "\nEnter sign(lt, gt, e) : ";
			std::string str;
			std::cin >> str;
			if (str == "lt") {
				sign = EquationSign::LessThan;
			}
			else if (str == "gt") {
				sign = EquationSign::GreaterThan;
			}
			else if (str == "e") {
				sign = EquationSign::Equal;
			}
		}
		equation.SetSign(sign);
		std::cout << "Enter b : ";
		double b;
		std::cin >> b;
		equation.SetB(b);
		break;
	}
	case EquationType::Problem:
	{
		std::cout << "\nEnter parameters number : ";
		double paramCount;
		std::cin >> paramCount;
		for (auto i = 0; i < paramCount; ++i) {
			int index;
			std::cout << "\nEnter param index : ";
			std::cin >> index;
			std::cout << "\nEnter coeficient near x[" << index << "] : ";
			double a;
			std::cin >> a;
			equation.SetCoeficient(index, a);
		}
		equation.SetSign(EquationSign::Equal);
		int b = 2;
		while (b == 2) {
			std::cout << "Enter the purpose of the proplem (Min(0) or Max(1)) : ";
			std::cin >> b;
			if (b == 0 || b == 1) {
				equation.SetB(b);
			}
		}
		break;
	}
	case EquationType::ParamSign:
	{
		int index;
		std::cout << "\nEnter param index : ";
		std::cin >> index;
		EquationSign sign = EquationSign::None;
		while (sign == EquationSign::None) {
			std::cout << "\nEnter sign(lt, gt, e) : ";
			std::string str;
			std::cin >> str;
			if (str == "lt") {
				sign = EquationSign::LessThan;
			}
			else if (str == "gt") {
				sign = EquationSign::GreaterThan;
			}
			else if (str == "e") {
				sign = EquationSign::Equal;
			}
			else if (str == "ne") {
				sign = EquationSign::NotEqual;
			}
		}
		equation.SetCoeficient(index, 1);
		equation.SetSign(sign);
		equation.SetB(0);
		break;
	}
	}
	return equation;
}

Equation Equation::CreateFromFile(const EquationType& type, nlohmann::json& parsedJson, int index) {
	Equation equation;
	equation.SetType(type);
	switch (type)
	{
	case EquationType::Simple:
	{
		auto& parsedEquation = parsedJson.at("Equations").at("Vector")[index];
		int paramCount = parsedEquation.at("Coeficients").at("Count").get<int>();
		for (auto i = 0; i < paramCount; ++i) {
			int paramIndex = parsedEquation.at("Coeficients").at("Vector")[i].at("index").get<int>();
			double a = parsedEquation.at("Coeficients").at("Vector")[i].at("value").get<double>();
			equation.SetCoeficient(paramIndex, a);
		}
		int signNumber = parsedEquation.at("Sign").get<int>();
		switch (signNumber)
		{
		case 0: {
			equation.SetSign(EquationSign::LessThan);
			break;
		}
		case 1: {
			equation.SetSign(EquationSign::GreaterThan);
			break;
		}
		case 2: {
			equation.SetSign(EquationSign::Equal);
			break;
		}
		case 3: {
			equation.SetSign(EquationSign::NotEqual);
			break;
		}
		}
		int b = parsedEquation.at("B").get<double>();
		equation.SetB(b);
		break;
	}
	case EquationType::Problem:
	{
		auto& parsedEquation = parsedJson.at("Problem");
		int paramCount = parsedEquation.at("Coeficients").at("Count").get<int>();
		for (auto i = 0; i < paramCount; ++i) {
			int paramIndex = parsedEquation.at("Coeficients").at("Vector")[i].at("index").get<int>();
			double a = parsedEquation.at("Coeficients").at("Vector")[i].at("value").get<double>();
			equation.SetCoeficient(paramIndex, a);
		}
		int b = parsedEquation.at("Purpose").get<int>();
		equation.SetB(b);
		break;
	}
	case EquationType::ParamSign:
	{
		int signNumber = parsedJson.at("Parameters").at("Vector")[index].get<int>();
		equation.SetCoeficient(index, 1);
		switch (signNumber)
		{
		case 0: {
			equation.SetSign(EquationSign::LessThan);
			break;
		}
		case 1: {
			equation.SetSign(EquationSign::GreaterThan);
			break;
		}
		case 2: {
			equation.SetSign(EquationSign::Equal);
			break;
		}
		case 3: {
			equation.SetSign(EquationSign::NotEqual);
			break;
		}
		}
		equation.SetB(0);
		break;
	}
	}
	return equation;
}

Equation Equation::Create(const std::vector<std::pair<int, double>>& coefs, const EquationSign& sign, const double b) {
	Equation equation;
	for (auto& coef : coefs) {
		equation.SetCoeficient(coef.first, coef.second);
	}
	equation.SetSign(sign);
	equation.SetB(b);
	return equation;
}

Equation Equation::Create(const std::vector<int>& coefs, const EquationSign& sign, const double b) {
	Equation equation;
	for (int i = 1; i <= coefs.size(); ++i) {
		equation.SetCoeficient(i, coefs[i-1]);
	}
	equation.SetSign(sign);
	equation.SetB(b);
	return equation;
}