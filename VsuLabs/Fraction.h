#pragma once
#include "LongLong.h"
#include <string>

class Fraction
{
private:
	com::LongLong round;
	double fraction;

	const static double delta;
public:

	Fraction();
	Fraction(const double value);
	Fraction(const com::LongLong round, const double fraction);
	Fraction(const Fraction& other);

	Fraction operator+(const Fraction& other) const;
	Fraction operator-(const Fraction& other) const;
	Fraction operator/(const Fraction& other) const;
	Fraction operator*(const Fraction& other) const;

	bool operator==(const Fraction& other);
	bool operator!=(const Fraction& other);
	bool operator<(const Fraction& other);
	bool operator<=(const Fraction& other);
	bool operator>(const Fraction& other);
	bool operator>=(const Fraction& other);

	double toDouble();
};