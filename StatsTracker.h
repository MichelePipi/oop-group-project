#ifndef STATSTRACKER_H
#define STATSTRACKER_H

class StatsTracker {
private:
    double totalCookies;
    double cookiesPerSecond;
    int totalClicks;
    int upgradesPurchased;

public:
    StatsTracker()
        : totalCookies(0), cookiesPerSecond(0),
          totalClicks(0), upgradesPurchased(0) {}

    // Core stats
    double getCookies() const { return totalCookies; }
    double getCPS() const { return cookiesPerSecond; }
    int getClicks() const { return totalClicks; }
    int getUpgradesPurchased() const { return upgradesPurchased; }

    // Additions to stats
    void addCookies(double amount) { totalCookies += amount; }
    void subtractCookies(double amount) { totalCookies -= amount; }

    void addClick() { totalClicks++; }
    void setCPS(double cps) { cookiesPerSecond = cps; }
    void addUpgrade() { upgradesPurchased++; }

    // Reset/clear
    void reset() {
        totalCookies = 0;
        cookiesPerSecond = 0;
        totalClicks = 0;
        upgradesPurchased = 0;
    }
};

#endif // STATSTRACKER_H
