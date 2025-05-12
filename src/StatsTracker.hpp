#pragma once
#include <iostream>

class StatsTracker {
    private:
        int totalClicks = 0;
        int totalCookies = 0;

    public:
        void registerClick() { totalClicks++; }
        void addCookies(int amount) { totalCookies += amount; }

        void printStats() const {
            std::cout << "\n Stats \n";
            std::cout << "Total Clicks: " << totalClicks << "\n";
            std::cout << "Total Cookies Earned: " << totalCookies << "\n";
        }
};
