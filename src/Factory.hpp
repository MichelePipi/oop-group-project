#pragma once
#include "AutoGenerator.hpp"

// The Factory class represents a mid/late-game automatic generator.
// Inherits from AutoGenerator and provides specific cost-scaling logic.
class Factory : public AutoGenerator {
    
public:
    // Constructor:
    // Initializes the Factory with a base cost of 50 and base CPS of 0.5
    Factory();

    // Virtual destructor (defaulted) to support proper cleanup in polymorphic usage
    virtual ~Factory() = default;

    // Overrides getCost() to apply linear cost scaling:
    // Cost = baseCost + (level * 10)
    int getCost() const override;
};
