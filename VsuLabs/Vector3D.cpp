#include "Vector3D.h"

Vector3D::Vector3D()
    : Triad()
{}

Vector3D::Vector3D(float x, float y, float z)
    : Triad(x, y, z)
{}

Vector3D Vector3D::operator+(const Vector3D& other)
{
    Vector3D res(this->x + other.x, this->y + other.y, this->z + other.z);
    return res;
}

float Vector3D::operator*(const Vector3D& other)
{
    return this->x * other.x + this->y * other.y + this->z * other.z;
}
