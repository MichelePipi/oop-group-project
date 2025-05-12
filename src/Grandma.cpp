#include "Grandma.hpp"
#include <cmath>

Grandma::Grandma()
    : AutoGenerator("Grandma", 25, 0.35f) {}

int Grandma::getCost() const 
{
    return static_cast<int>(baseCost * pow(1.15f, level));

    
}
