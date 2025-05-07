#ifndef MANUAL_CLICKER_H
#define MANUAL_CLICKER_H

#include "ClickableItem.h"

class ManualClicker : public ClickableItem {
    private:
        int quantity;
        double price;
    public: 
        ManualClicker(double initialPrice = 5.0) : quantity(0), price(initialPrice) {}
        std::string getName() const override {
            return "Manual Clicker";
        }
        double getCookiesPerSecond() const override {
            return 0.0;
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
};

#endif