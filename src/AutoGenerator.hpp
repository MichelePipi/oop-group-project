#pragma once
#include "ClickableItem.hpp"
#include <memory>

// The AutoGenerator class represents automated cookie-producing entities,
// such as Factories, Autoclickers, and Grandmas.
// Inherits from ClickableItem and adds functionality for passive cookie generation.
class AutoGenerator : public ClickableItem {
    
protected:
    // Base cookies per second (CPS) provided by a single instance of this generator at level 1
    float baseCps;

public:
    // Constructor:
    // Initializes the generator with a name, base cost, and base CPS
    AutoGenerator(const std::string& name, int cost, float cps);

    // Generates cookies based on the current level and CPS.
    void generate(long long cookies) override;

    // Calculates and returns the current total CPS (baseCps * level)
    float getCps() const;

    // Returns a human-readable string showing generator status (name, level, CPS)
    std::string getStatus() const override;

    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~AutoGenerator() = default;
};
