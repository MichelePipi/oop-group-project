#pragma once
#include "ClickableItem.hpp"

// The ManualClicker class represents the player's basic tool for generating cookies.
// It inherits from ClickableItem and defines behavior for manual clicking.
class ManualClicker : public ClickableItem 
{
public:
    // Constructor:
    // Initializes a Manual Clicker with name "Manual Clicker" and a cost of 0
    ManualClicker();

    // Overrides the generate() method to add 1 cookie per click.
    void generate(long long cookies) override;

    // Returns a short description of what the Manual Clicker does
    std::string getStatus() const override;

    // Returns the cost to purchase/upgrade — always 0 for Manual Clicker
    int getCost() const override;

    // Virtual destructor (defaulted) for safe cleanup
    virtual ~ManualClicker() = default;
};
