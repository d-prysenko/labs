#pragma once
#include <cmath>

class Function
{
protected:
    float a;
    float b;

public:
    virtual float calculateY(float x) = 0;

    Function()
        : a(1), b(1)
    {}

    Function(float a, float b)
        : a(a), b(b)
    {}
};

class Ellipse : public Function
{
public:
    Ellipse()
        : Function()
    {}

    Ellipse(float a, float b)
        : Function(a, b)
    {}

    virtual float calculateY(float x)
    {
        return sqrt((1 - (x * x) / (a * a)) * (b * b));
    }
};

class Hyperbola : public Function
{
public:
    Hyperbola()
        : Function()
    {}

    Hyperbola(float a, float b)
        : Function(a, b)
    {}

    virtual float calculateY(float x)
    {
        return sqrt(((x * x) / (a * a) - 1) * (b * b));
    }
};
