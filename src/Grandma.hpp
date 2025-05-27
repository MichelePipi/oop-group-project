#pragma once
#include "AutoGenerator.hpp"

// The Grandma class represents an early-game automatic cookie generator.
// Inherits from AutoGenerator and defines custom cost-scaling logic.
class Grandma : public AutoGenerator {

public:
    // Constructor:
    // Initializes a Grandma with a base cost of 25 cookies and base CPS of 0.35
    Grandma();

    // Virtual destructor (defaulted) for proper cleanup in polymorphic use
    virtual ~Grandma() = default;

    // Overrides getCost() to apply 15% exponential cost scaling:
    // cost = baseCost * (1.15 ^ level)
    int getCost() const override;
};
