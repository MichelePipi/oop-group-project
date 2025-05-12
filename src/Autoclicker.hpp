#pragma once
#include "AutoGenerator.hpp"

class Autoclicker : public AutoGenerator 
{

    public:
        Autoclicker();
        int getCost() const override;
};
