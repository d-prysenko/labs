#include "Fraction.h"

const double Fraction::delta = 0.0001;

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
	com::LongLong precision(10000);

	com::LongLong l = (com::LongLong(this->round) * precision) + (com::LongLong(this->fraction) * precision);
	com::LongLong r = (com::LongLong(other.round) * precision) + (com::LongLong(other.fraction) * precision);

	com::LongLong number(l / r);

	double remind = (double)(l - (number * r)).toLL() / r.toLL();

	return Fraction(number, remind);
}

Fraction Fraction::operator*(const Fraction& other) const
{
	com::LongLong precision(10000);

	com::LongLong l = (com::LongLong(this->round) * precision) + (com::LongLong(this->fraction * 10000));
	com::LongLong r = (com::LongLong(other.round) * precision) + (com::LongLong(other.fraction * 10000));

	com::LongLong number = l * r;

	com::LongLong round = number / (precision * precision);
	double remind = (double)(number - (round * (precision * precision))).toLL() / (precision * precision).toLL();

	return Fraction(round, remind);
}

bool Fraction::operator==(const Fraction& other)
{
	return this->round == other.round && abs(this->fraction - other.fraction) <= Fraction::delta;
}

bool Fraction::operator!=(const Fraction& other)
{
	return !this->operator==(other);
}

bool Fraction::operator<(const Fraction& other)
{
	return this->round < other.round && this->fraction < other.fraction;
}

bool Fraction::operator<=(const Fraction& other)
{
	return this->round <= other.round && (this->fraction <= other.fraction || abs(this->fraction - other.fraction) <= Fraction::delta);
}

bool Fraction::operator>(const Fraction& other)
{
	return this->round > other.round && this->fraction > other.fraction;
}

bool Fraction::operator>=(const Fraction& other)
{
	return this->round >= other.round && (this->fraction >= other.fraction || abs(this->fraction - other.fraction) <= Fraction::delta);
}

double Fraction::toDouble()
{
	return this->round.toLL() + this->fraction;
}