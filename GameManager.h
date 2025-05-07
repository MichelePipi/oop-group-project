#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <memory>
#include "ClickableItem.h"
#include "Upgrade.h"
#include "StatsTracker.h"

class GameManager {
private:
    double totalCookies;
    bool running;

    StatsTracker stats;

    std::vector<std::shared_ptr<ClickableItem>> generators;
    std::vector<std::shared_ptr<Upgrade>> upgrades;

public:
    GameManager();

    void run();
    void displayMenu();
    void handleInput(int choice);
    void updateGenerators(double deltaTime);
    void purchaseUpgradeMenu();

    void addGenerator(std::shared_ptr<ClickableItem> generator);
    void addUpgrade(std::shared_ptr<Upgrade> upgrade);
};

#endif // GAME_MANAGER_H
