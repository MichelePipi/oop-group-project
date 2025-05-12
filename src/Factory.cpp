#include "Factory.hpp"

Factory::Factory()
    : AutoGenerator("Factory", 50, 0.5f) {}

int Factory::getCost() const {
    return baseCost + (level * 10);
}
