#include "Autoclicker.hpp"
#include <cmath> // For using pow() to calculate exponential cost scaling

// Constructor: Initializes an Autoclicker with default values
// Name: "Autoclicker", Base Cost: 5 cookies, CPS: 0.05 per unit
Autoclicker::Autoclicker() 
    : AutoGenerator("Autoclicker", 5, 0.05f) {}

// Returns the current cost of purchasing the next Autoclicker
// Cost increases by 10% for each Autoclicker already owned
int Autoclicker::getCost() const 
{
    // Uses exponential growth: cost = baseCost * (1.10 ^ level)
    // Example: 5 * (1.10 ^ 3) for level 3
    return static_cast<int>(baseCost * pow(1.10f, level));
}
