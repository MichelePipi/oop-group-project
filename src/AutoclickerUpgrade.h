// AutoclickerUpgrade.h
#ifndef AUTOCLICKERUPGRADE_H
#define AUTOCLICKERUPGRADE_H

#include "Upgrade.h"
#include "AutoGenerator.h"
#include <memory>

class AutoclickerUpgrade : public Upgrade {
private:
    std::shared_ptr<AutoGenerator> autoclicker;

public:
    AutoclickerUpgrade(std::shared_ptr<AutoGenerator> autoclicker)
        : Upgrade("Autoclicker++", 500.0), autoclicker(autoclicker) {}

    void applyUpgrade() override {
        if (!purchased && autoclicker) {
            autoclicker->applyMultiplier(2.0);  // double CPS
            purchased = true;
        }
    }
};

#endif // AUTOCLICKERUPGRADE_H
