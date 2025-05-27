#pragma once
#include <string>

// Abstract base class for any item that can generate cookies.
// This includes manual clickers and automated generators like factories or grandmas.
// It provides shared attributes (name, cost, level) and a common interface for derived classes.
class ClickableItem {
    
protected:
    std::string name;     // Name of the item (e.g., "Factory", "Autoclicker")
    int baseCost;         // Base cost of the item (initial cost before scaling)
    int level;            // Current level or quantity of the item purchased

public:
    // Constructor: Initializes the item with a name and base cost, sets level to 0
    ClickableItem(const std::string& name, int cost)
        : name(name), baseCost(cost), level(0) {}

    // Virtual destructor for safe polymorphic use
    virtual ~ClickableItem() = default;

    // Pure virtual function: generates cookies based on item type and level
    // Must be overridden in derived classes
    virtual void generate(long long cookies) = 0;

    // Pure virtual function: returns a string representation of the item's status
    virtual std::string getStatus() const = 0;

    // Pure virtual function: calculates and returns the cost to purchase/upgrade this item
    virtual int getCost() const = 0;

    // Accessor: Returns the item’s name
    std::string getName() const { return name; }

    // Accessor: Returns the current level
    int getLevel() const { return level; }

    // Mutator: Increases the item’s level by one
    void increaseLevel() { level++; }

    // Mutator: Sets the item’s level to a specific value
    void setLevel(int l) { this->level = l; }
};
