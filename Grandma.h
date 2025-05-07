// Grandma.h
#ifndef GRANDMA_H
#define GRANDMA_H

#include "AutoGenerator.h"

class Grandma : public AutoGenerator {
public:
    // Constructor sets the initial price and CPS specific to Grandma
    Grandma() : AutoGenerator(25.0, 0.35) {}

    std::string getName() const override {
        return "Grandma";
    }

    // Override purchase logic to increase price by 15% each time
    void purchase() override {
        quantity++;
        price += price * 0.15;  // 15% price increase per grandma purchased
    }
};

#endif // GRANDMA_H
