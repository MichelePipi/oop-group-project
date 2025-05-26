#pragma once
#include "AutoGenerator.hpp"

class Factory : public AutoGenerator {
    public:
        Factory();
        virtual ~Factory() = default;
        int getCost() const override;
};
