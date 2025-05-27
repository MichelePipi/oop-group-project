#pragma once
#include <vector>
#include <memory>
#include "ClickableItem.hpp"
#include "AutoGenerator.hpp"
#include "StatsTracker.hpp"
#include "SaveFileManager.hpp"


class GameManager {
    private:
        long long cookies;
        std::unique_ptr<ClickableItem> manualClicker;
        StatsTracker stats;
    public:
        GameManager();
        bool hasGoldenDough;
        std::vector<std::unique_ptr<AutoGenerator>> generators;

        // generator/ui handlers
        void handleChoice(int choice);
        void showGenerators();
        void runAutoGeneration();

        // GUI helpers
        int getCookieCount() const;
        float calculateTotalCps() const;
        int getGeneratorCost(int index) const;
        int getGeneratorLevel(int index) const;
        void setCookies(long long c);
        void loadSaveData(const std::vector<double> &variables);
        SaveFileManager saveFile;
};
