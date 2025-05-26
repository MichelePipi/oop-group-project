#pragma once
#include "AutoGenerator.hpp"

class Autoclicker : public AutoGenerator 
{

    public:
        Autoclicker();
        virtual ~Autoclicker() = default;
        int getCost() const override;
};
