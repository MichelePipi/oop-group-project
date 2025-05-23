#include "ManualClicker.hpp"

ManualClicker::ManualClicker(): ClickableItem("Manual Clicker", 0) {}

void ManualClicker::generate(int& cookies) 
{
    cookies += 1;
}

std::string ManualClicker::getStatus() const 
{
    return "Manual Clicker: click to earn 1 cookie.";
}

int ManualClicker::getCost() const 
{
    return 0;
}