#include "Grandma.hpp"
#include <cmath> // For pow() to handle exponential cost scaling

// Constructor:
// Initializes a Grandma generator with:
// Name: "Grandma", Base Cost: 25 cookies, Base CPS: 0.35 cookies/second
Grandma::Grandma()
    : AutoGenerator("Grandma", 25, 0.35f) {}

// Calculates and returns the cost of purchasing the next Grandma.
// Cost increases by 15% for each Grandma already owned.
// Formula: cost = baseCost * (1.15 ^ level)
int Grandma::getCost() const 
{
    return static_cast<int>(baseCost * pow(1.15f, level));
}
