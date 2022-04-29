#include "Triad.h"

Triad::Triad()
	: x(0), y(0), z(0)
{}

Triad::Triad(float x, float y, float z)
	: x(x), y(y), z(z)
{}

Triad::Triad(const Triad & other)
	:x(other.x), y(other.y), z(other.z)
{}



float Triad::getX()
{
	return this->x;
}

void Triad::setX(float x)
{
	this->x = x;
}

float Triad::getY()
{
	return this->y;
}

void Triad::setY(float y)
{
	this->y = y;
}

float Triad::getZ()
{
	return this->z;
}

void Triad::setZ(float z)
{
	this->z = z;
}

Triad Triad::operator+(float number)
{
	Triad res(this->x + number, this->y + number, this->z + number);
	return res;
}

Triad Triad::operator*(float number)
{
	Triad res(this->x * number, this->y * number, this->z * number);
	return res;
}

bool Triad::operator==(const Triad& vec)
{
	return this->x == vec.x && this->y == vec.y && this->z == vec.z;
}

Triad& Triad::operator=(const Triad& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}
