#pragma once
#include "AutoGenerator.hpp"

class Grandma : public AutoGenerator {
    public:
        Grandma();
        virtual ~Grandma() = default;
        int getCost() const override;
};
