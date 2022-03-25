#include "Angle.h"

Angle::Angle()
	: p_degrees(new int()), p_minutes(new int())
{}

Angle::Angle(int degrees, int minutes)
	: p_degrees(new int(degrees)), p_minutes(new int(minutes))
{}

Angle::Angle(const Angle& other)
	: p_degrees(new int(*other.p_degrees)), p_minutes(new int(*other.p_minutes))
{}

Angle::~Angle()
{
	delete p_degrees;
	delete p_minutes;
}

int Angle::to_minutes() const
{
	return (*this->p_degrees) * 60 + *this->p_minutes;
}

Angle Angle::operator+(const Angle& other)
{
	int minutes = this->to_minutes() + other.to_minutes();

	Angle res(minutes / 60, minutes % 60);
	return res;
}

Angle& Angle::operator-(const Angle& other)
{
	int minutes = this->to_minutes() + other.to_minutes();

	Angle res(minutes / 60, minutes % 60);
	return res;
}

Angle& Angle::operator/(const Angle& other)
{
	int minutes = this->to_minutes() / other.to_minutes();

	Angle res(minutes / 60, minutes % 60);
	return res;
}

Angle& Angle::operator*(const Angle& other)
{
	int minutes = this->to_minutes() * other.to_minutes();

	Angle res(minutes / 60, minutes % 60);
	return res;
}

Angle& Angle::operator/(const int other)
{
	int minutes = this->to_minutes() / other;

	Angle res(minutes / 60, minutes % 60);
	return res;
}

Angle& Angle::operator*(const int other)
{
	int minutes = this->to_minutes() * other;

	Angle res(minutes / 60, minutes % 60);
	return res;
}

bool Angle::operator==(const Angle& other)
{
	return (*this->p_degrees == *other.p_degrees) && (*this->p_minutes == *other.p_minutes);
}

bool Angle::operator!=(const Angle& other)
{
	return !operator==(other);
}

bool Angle::operator>(const Angle& other)
{
	return this->to_minutes() > other.to_minutes();
}

bool Angle::operator>=(const Angle& other)
{
	return this->to_minutes() >= other.to_minutes();
}

bool Angle::operator<(const Angle& other)
{
	return this->to_minutes() < other.to_minutes();
}

bool Angle::operator<=(const Angle& other)
{
	return this->to_minutes() <= other.to_minutes();
}

Angle& Angle::operator=(const Angle& other)
{
	*this->p_degrees = *other.p_degrees;
	*this->p_minutes = *other.p_minutes;
	return *this;
}

std::wostream& operator<<(std::wostream& stream, const Angle& angle)
{
	return stream << *angle.p_degrees << "°" << *angle.p_minutes << "'";
}

std::wistream& operator>>(std::wistream& stream, const Angle& angle)
{
	int minutes;
	stream >> *angle.p_degrees >> minutes;

	*angle.p_degrees += minutes / 60;
	*angle.p_minutes = minutes % 60;

	return stream;
}