#ifndef GOLDENDOUGHUPGRADE_H
#define GOLDENDOUGHUPGRADE_H

#include "Upgrade.h"
#include "ClickableItem.h"
#include <vector>
#include <memory>

class GoldenDoughUpgrade : public Upgrade {
private:
    std::vector<std::shared_ptr<ClickableItem>> generators; // Vector of generators (Clickables)

public:
    // Constructor updated to accept std::vector<std::shared_ptr<ClickableItem>>
    GoldenDoughUpgrade(const std::vector<std::shared_ptr<ClickableItem>> &generators)
        : Upgrade(5000), generators(generators) {}

    virtual void apply() override {
        // Doubles the effect of all generators (cps).
        for (auto& generator : generators) {
            // Only apply the upgrade to AutoGenerators
            auto autoGen = std::dynamic_pointer_cast<AutoGenerator>(generator);
            if (autoGen) {
                double newCPS = autoGen->getCookiesPerSecond() * 2; // Double the CPS
                // Update the CPS or apply any necessary changes to your game logic
                // autoGen->setCPS(newCPS); // Uncomment if AutoGenerator has a setter for CPS
            }
        }
    }

    virtual std::string getName() const override {
        return "Golden Dough Upgrade";
    }
};

#endif
