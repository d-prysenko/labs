#pragma once
#include "Triad.h"

class Vector3D : public Triad
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);

	Vector3D operator+(const Vector3D& other);
	float operator*(const Vector3D& other);
};

