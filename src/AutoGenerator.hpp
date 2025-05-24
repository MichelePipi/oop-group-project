#pragma once
#include "ClickableItem.hpp"

class AutoGenerator : public ClickableItem {
    protected:
        float baseCps;

    public:
        AutoGenerator(const std::string& name, int cost, float cps);
        void generate(int& cookies) override;
        virtual float getCps() = 0;
        std::string getStatus() const override;
};
