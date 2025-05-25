#pragma once
#include "ClickableItem.hpp"

class ManualClicker : public ClickableItem 
{
    public:
        ManualClicker();
        void generate(long long cookies) override;
        std::string getStatus() const override;
        int getCost() const override;
};