#include "Autoclicker.hpp"
#include <cmath>

Autoclicker::Autoclicker()
    : AutoGenerator("Autoclicker", 5, 0.05f) {}

int Autoclicker::getCost() const 
{
    return static_cast<int>(baseCost * pow(1.10f, level));
}
