#pragma once
class Triad
{
protected:
	float x, y, z;

public:
	Triad();
	Triad(float x, float y, float z);
	Triad(const Triad& other);

	float getX();
	void setX(float x);

	float getY();
	void setY(float y);

	float getZ();
	void setZ(float z);

	Triad operator+(float number);
	Triad operator*(float number);
	bool operator==(const Triad& vec);

	Triad& operator=(const Triad& other);
};

