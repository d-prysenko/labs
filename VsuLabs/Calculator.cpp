#include "Calculator.h"

Calculator::Calculator()
{}

Calculator::Calculator(const Calculator& other)
{}

Fraction Calculator::sum(const Fraction& right, const Fraction& left)
{
	return right + left;
}

Fraction Calculator::diff(const Fraction& right, const Fraction& left)
{
	return right - left;
}

Fraction Calculator::mult(const Fraction& right, const Fraction& left)
{
	return right * left;
}

Fraction Calculator::div(const Fraction& right, const Fraction& left)
{
	return right / left;
}
