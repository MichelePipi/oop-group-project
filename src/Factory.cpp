#include "Factory.hpp"

// Constructor:
// Initializes a Factory with:
// Name: "Factory", Base Cost: 50 cookies, Base CPS: 0.5 cookies/second
Factory::Factory() 
    : AutoGenerator("Factory", 50, 0.5f) {}

// Returns the cost to purchase the next Factory.
// The cost increases linearly by 10 cookies per factory owned.
// Example: level 3 → 50 + (3 * 10) = 80 cookies
int Factory::getCost() const {
    return baseCost + (level * 10);
}
