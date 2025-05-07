#ifndef CLICKABLE_ITEM_H
#define CLICKABLE_ITEM_H
#include <string>


class ClickableItem {
    public:
        virtual ~ClickableItem() = default;

        virtual std::string getName() const = 0;
        virtual double getCookiesPerSecond() const = 0;
        virtual double getPrice() const = 0;
        virtual void purchase() = 0;
        virtual int getQuantity() const = 0;


};

#endif