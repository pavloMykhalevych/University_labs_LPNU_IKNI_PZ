#include "Equation.h"

#include <iostream>
#include <string>

void Equation::Create(int paramCount) {
	for (auto i = 0; i < paramCount; ++i) {
		std::cout << "Enter a[" << i + 1 << "] : ";
		double a;
		std::cin >> a;
		m_a.push_back(a);
	}
	EquationSign sign = EquationSign::None;
	while (sign == EquationSign::None) {
		std::cout << "Enter sign(lt, gt, e) : ";
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
	m_sign = sign;
	std::cout << "Enter b : ";
	double b;
	std::cin >> b;
	m_b = b;
}

std::vector<double> Equation::GetCoeficients() const {
	return m_a;
}

double Equation::GetB() const {
	return m_b;
}


void Equation::ConvertToCanonical() {

}