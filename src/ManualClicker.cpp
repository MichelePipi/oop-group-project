#include "ManualClicker.hpp"

// Constructor:
// Initializes the Manual Clicker with the name "Manual Clicker" and a cost of 0.
// This represents the basic method of earning cookies by clicking.
ManualClicker::ManualClicker()
    : ClickableItem("Manual Clicker", 0) {}

// Generates cookies through manual clicking.
void ManualClicker::generate(long long cookies)
{
    cookies += 1;
}

// Returns a fixed status string describing what the manual clicker does
std::string ManualClicker::getStatus() const 
{
    return "Manual Clicker: click to earn 1 cookie.";
}

// Returns the cost of the Manual Clicker (always 0)
int ManualClicker::getCost() const 
{
    return 0;
}
