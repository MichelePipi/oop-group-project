#pragma once
#include <iostream>

// StatsTracker is a utility class for tracking and displaying user statistics,
// such as total manual clicks and total cookies earned during gameplay.
class StatsTracker {
private:
    int totalClicks = 0;    // Number of times the user manually clicked the cookie
    int totalCookies = 0;   // Total cookies earned throughout the session (manual + auto)

public:
    // Increments the click counter by one
    void registerClick() { totalClicks++; }

    // Adds the specified amount of cookies to the total count
    void addCookies(int amount) { totalCookies += amount; }

    // Displays the statistics in the console
    void printStats() const {
        std::cout << "\n Stats \n";
        std::cout << "Total Clicks: " << totalClicks << "\n";
        std::cout << "Total Cookies Earned: " << totalCookies << "\n";
    }
};
