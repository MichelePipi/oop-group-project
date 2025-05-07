#ifndef AUTOCLICKER_H
#define AUTOCLICKER_H

#include "AutoGenerator.h"

class Autoclicker : public AutoGenerator {
    public:
        Autoclicker() : AutoGenerator(5.0, 0.05) {}

        std::string getName() const override {
            return "Autoclicker";
        }
};


#endif