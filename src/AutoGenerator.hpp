#pragma once
#include "ClickableItem.hpp"
#include <memory>

class AutoGenerator : public ClickableItem {
    protected:
        float baseCps;

    public:
        AutoGenerator(const std::string& name, int cost, float cps);
        void generate(long long cookies) override;
        float getCps() const;
        std::string getStatus() const override;
        virtual ~AutoGenerator() = default;

};
