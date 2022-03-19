#pragma once

#include <vector>

#include "EquationSign.h"

class Equation
{
public:
	void Create(int paramCount);

	std::vector<double> GetCoeficients() const;

	double GetB() const;

	void ConvertToCanonical();
private:
	std::vector<double> m_a;
	double m_b;
	EquationSign m_sign;
};

