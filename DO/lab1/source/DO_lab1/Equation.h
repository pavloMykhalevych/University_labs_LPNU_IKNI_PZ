#pragma once

#include <json.h>

#include <iostream>
#include <vector>
#include <filesystem>

#include "EquationSign.h"
#include "EquationType.h"

class Equation
{
public:
	static Equation Create(const EquationType& type);
	static Equation CreateFromFile(const EquationType& type, nlohmann::json& parsedJson, int index = 0);

	std::vector<std::pair<int, double>>& GetCoeficients();
	void SetCoeficient(const int paramIndex, const double a);
	void SetCoeficient(const int index, const int paramIndex, const double a);

	double& GetB();
	void SetB(const double b);

	const EquationSign& GetSign() const;
	void SetSign(const EquationSign& sign);

	const EquationType& GetType() const;
	void SetType(const EquationType& type);

private:
	std::vector<std::pair<int, double>> m_a;
	double m_b;
	EquationSign m_sign;
	EquationType m_type;
};

