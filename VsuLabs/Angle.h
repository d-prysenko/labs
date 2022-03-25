#pragma once
#include <iostream>

class Angle
{
private:

	int* p_degrees;
	int* p_minutes; // 1/60 of degree

	int to_minutes() const;

public:

	Angle();
	Angle(int degrees, int minutes);
	Angle(const Angle& other);
	~Angle();

	Angle operator+(const Angle& other);
	Angle operator-(const Angle& other);
	Angle operator/(const Angle& other);
	Angle operator*(const Angle& other);
	Angle operator/(const int other);
	Angle operator*(const int other);

	bool operator==(const Angle& other);
	bool operator!=(const Angle& other);
	bool operator>(const Angle& other);
	bool operator>=(const Angle& other);
	bool operator<(const Angle& other);
	bool operator<=(const Angle& other);

	Angle& operator=(const Angle& other);

	friend std::wostream& operator<<(std::wostream& stream, const Angle& angle);
	friend std::wistream& operator>>(std::wistream& stream, const Angle& angle);
};