#pragma once
#include "AutoGenerator.hpp"

// The Autoclicker class represents a low-tier automatic cookie generator.
// It inherits from AutoGenerator and defines custom behavior like cost scaling.
class Autoclicker : public AutoGenerator 
{
    public:
        // Constructor: Initializes an Autoclicker with a base cost and CPS
        Autoclicker();

        // Virtual destructor (defaulted) to ensure proper cleanup in polymorphic use
        virtual ~Autoclicker() = default;

        // Overrides the base class method to calculate cost with exponential growth
        // Increases cost by 10% per Autoclicker already purchased
        int getCost() const override;
};
