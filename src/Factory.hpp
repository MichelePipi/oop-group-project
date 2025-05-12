#pragma once
#include "AutoGenerator.hpp"

class Factory : public AutoGenerator {
    public:
        Factory();
        int getCost() const override;
};
