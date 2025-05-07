#ifndef UPGRADE_H
#define UPGRADE_H

#include <string>

class Upgrade {

    protected:
        std::string name;
        double price;
        double purchased;

    public:
        Upgrade(const std::string& name, double price) : name(name), price(price), purchased(false) {}

        virtual ~Upgrade() {}

        virtual void applyUpgrade() = 0;
        virtual bool isPurchased() const {
            return purchased;
        }

        virtual double getPrice() const {
            return price;
        }

        virtual std::string getName() const {
            return name;
        }
        
        virtual void purchaseUpgrade() {
            purchased = true;
        }
};

#endif