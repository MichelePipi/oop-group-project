#pragma once
#include <string>

class ClickableItem {
    protected:
        std::string name;
        int baseCost;
        int level;

    public:
        ClickableItem(const std::string& name, int cost)
            : name(name), baseCost(cost), level(0) {}

        virtual ~ClickableItem() = default;

        virtual void generate(long long cookies) = 0;
        virtual std::string getStatus() const = 0;
        virtual int getCost() const = 0;

        std::string getName() const { return name; }
        int getLevel() const { return level; }
        void increaseLevel() { level++; }
        void setLevel(int l) { this->level = l; }
};
