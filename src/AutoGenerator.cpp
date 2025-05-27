#include "AutoGenerator.hpp"

AutoGenerator::AutoGenerator(const std::string& name, int cost, float cps) : ClickableItem(name, cost), baseCps(cps) {}

void AutoGenerator::generate(long long cookies)
{
    cookies += static_cast<int>(getCps());
}

float AutoGenerator::getCps() const {
    return baseCps * level;
}

std::string AutoGenerator::getStatus() const {
    return name + " (Lvl " + std::to_string(level) + ") - CPS: " + std::to_string(getCps());
}
