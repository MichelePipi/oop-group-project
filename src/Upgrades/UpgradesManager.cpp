#include "UpgradesManager.h"
#include "Upgrade.h"
//#include "GenericUpgrade.h"
#include <iostream>

UpgradesManager::UpgradesManager() {
    // implement genericupgrades
    std::vector<GenericUpgrade> upgrades;
}

UpgradesManager::UpgradesManager(Upgrade** u) {
    upgrades = u; 
}