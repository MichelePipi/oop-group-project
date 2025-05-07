#ifndef AUTO_GENERATOR_H
#define AUTO_GENERATOR_H

#include "ClickableItem.h"

class AutoGenerator : public ClickableItem {
    protected:
        int quantity;
        double price;
        double cps;
        double cpsPerUnit;
        double multiplier = 1.0; 

    public:
        AutoGenerator(double initialPrice, double initialCps) : quantity(0), price(initialPrice),cps(initialCps) {}

        std::string getName() const override {
            return "Auto Generator";
        }

        double getCookiesPerSecond() const override {
            return cps * quantity;
        }

        double getPrice() const override {
            return price;
        }

        void purchase() override {
            quantity++;
            price *= 1.15; // Increase price by 15% for the next purchase
        }

        int getQuantity() const override {
            return quantity;
        }
        void applyMultiplier(double multiplier) {
            cpsPerUnit *= multiplier;
        }
        


};

#endif