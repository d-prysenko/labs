#include "Fraction.h"

Fraction::Fraction()
	: round(0), fraction(0)
{}

Fraction::Fraction(double value)
	: round(value), fraction(value - (long)value)
{}

Fraction::Fraction(const com::LongLong round, const double fraction)
	: round(round), fraction(fraction)
{}

Fraction::Fraction(const Fraction& other)
	: round(other.round), fraction(other.fraction)
{}

Fraction Fraction::operator+(const Fraction& other) const
{
	double temp = this->fraction + other.fraction;

	Fraction res(this->round + other.round + (long)temp, temp - (long)temp);
	return res;
}

Fraction Fraction::operator-(const Fraction& other) const
{
	double res_fraction = this->fraction - other.fraction;
	com::LongLong res_round = this->round - other.round;

	if (res_fraction < 0) {
		res_round = res_round - 1;
		res_fraction = 1.0 + res_fraction;
	}

	Fraction res(res_round, res_fraction);
	return res;
}

Fraction Fraction::operator/(const Fraction& other) const
{
	com::LongLong l = com::LongLong(this->round * 10000000) + com::LongLong(this->fraction * 10000000);
	com::LongLong r = com::LongLong(other.round * 10000000) + com::LongLong(other.fraction * 10000000);

	com::LongLong number(l / r);

	Fraction res(number / 10000000, (number - (number / 10000000)));
	return res;
}

Fraction Fraction::operator*(const Fraction& other) const
{
	return Fraction();
}

bool Fraction::operator==(const Fraction& other)
{
	return false;
}

bool Fraction::operator!=(const Fraction& other)
{
	return false;
}

bool Fraction::operator<(const Fraction& other)
{
	return false;
}

bool Fraction::operator<=(const Fraction& other)
{
	return false;
}

bool Fraction::operator>(const Fraction& other)
{
	return false;
}

bool Fraction::operator>=(const Fraction& other)
{
	return false;
}
