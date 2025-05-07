// Factory.h
#ifndef FACTORY_H
#define FACTORY_H

#include "AutoGenerator.h"

class Factory : public AutoGenerator {
public:
    // Constructor with base price 50 and CPS 0.5
    Factory() : AutoGenerator(50.0, 0.5) {}

    std::string getName() const override {
        return "Factory";
    }

    // Override purchase logic to use flat +10 price increase
    void purchase() override {
        quantity++;
        price += 10.0;  // Flat +10 increase per factory bought
    }
};

#endif // FACTORY_H
