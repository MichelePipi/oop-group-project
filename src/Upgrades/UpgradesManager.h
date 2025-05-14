#ifndef UPGRADES_MANAGER_H
#define UPGRADES_MANAGER_H

#include "Upgrade.h"

class UpgradesManager {
    private:
        Upgrade** upgrades;
        int cps;
    public:
        UpgradesManager(); 
        UpgradesManager(Upgrade** u);
        int calculateCurrentCps();
};

#endif 