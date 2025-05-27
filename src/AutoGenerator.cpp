#include "AutoGenerator.hpp"

// Constructor:
// Initializes an AutoGenerator with a given name, base cost, and cookies-per-second (CPS) rate.
// It calls the ClickableItem constructor to set name and cost,
// and sets the base CPS value unique to this generator type.
AutoGenerator::AutoGenerator(const std::string& name, int cost, float cps)
    : ClickableItem(name, cost), baseCps(cps) {}

// Cookie generation logic for auto-generators (e.g., factories, grandmas).
// Adds cookies based on current CPS. Note: cookies is passed by value here,
// so this function currently does not modify the actual game state unless rewritten.
void AutoGenerator::generate(long long cookies)
{
    cookies += static_cast<long long>(getCps()); // Adds current CPS to the cookie count (ineffective unless cookies is passed by reference)
}

// Calculates current cookies per second (CPS) based on generator level.
// Example: level 3 and baseCps 0.5 = 1.5 CPS
float AutoGenerator::getCps() const {
    return baseCps * level;
}

// Returns a status string showing the generator's name, level, and current CPS.
// Example: "Factory (Lvl 2) - CPS: 1.00"
std::string AutoGenerator::getStatus() const {
    return name + " (Lvl " + std::to_string(level) + ") - CPS: " + std::to_string(getCps());
}
