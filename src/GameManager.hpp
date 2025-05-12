#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include "ClickableItem.hpp"
#include "ManualClicker.hpp"
#include "AutoGenerator.hpp"
#include "Factory.hpp"
#include "Grandma.hpp"
#include "Autoclicker.hpp"
#include "StatsTracker.hpp"

class GameManager {
    private:
        int cookies;
        std::unique_ptr<ClickableItem> manualClicker;
        std::vector<std::unique_ptr<AutoGenerator>> generators;
        StatsTracker stats;

    public:
        GameManager();

        void startGame();
        void displayMenu();
        void handleChoice(int choice);
        void showGenerators();
        void runAutoGeneration();
        void saveGame();
        void loadGame();

        // GUI helpers
        int getCookieCount() const;
        float calculateTotalCps() const;
        int getGeneratorCost(int index) const;
        int getGeneratorLevel(int index) const;
};
