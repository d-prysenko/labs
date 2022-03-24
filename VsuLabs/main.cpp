#include <iostream>
#include <string>
#include "Function.h"

std::string pretty_print(float x, float y)
{
    if (isnan(y)) {
        return "no solutions. unable to find f(" + std::to_string(x) + "). probably function is not defined at the point.";
    } else {
        return "f(" + std::to_string(x) + ") = " + std::to_string(y);
    }
}

int main()
{
    Function* ellipse = new Ellipse(2, 1);
    Function* hyperbola = new Hyperbola(4, 4);

    float ellipseY = ellipse->calculateY(1);

    std::cout << "ellipse: " << pretty_print(1, ellipse->calculateY(1)) << std::endl;
    std::cout << "ellipse: " << pretty_print(10, ellipse->calculateY(10)) << std::endl;
    std::cout << "hyperbola: " << pretty_print(5, hyperbola->calculateY(5)) << std::endl;

    system("pause");
    return 0;
}