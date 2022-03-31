#pragma once
#include "Fraction.h"

class Calculator
{
public:

	Calculator();
	Calculator(const Calculator& other);

	Fraction sum(const Fraction& right, const Fraction& left);
	Fraction diff(const Fraction& right, const Fraction& left);
	Fraction mult(const Fraction& right, const Fraction& left);
	Fraction div(const Fraction& right, const Fraction& left);


};