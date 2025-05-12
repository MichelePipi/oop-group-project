#pragma once
#include "AutoGenerator.hpp"

class Grandma : public AutoGenerator {
    public:
        Grandma();
        int getCost() const override;
};
