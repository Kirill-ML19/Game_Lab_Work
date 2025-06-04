#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class ItemType {
    WEAPON,
    ARMOR,
    HEALTH_POTION,
    STRENGTH_POTION,
    DEFENSE_POTION,
    MISC
};

class Item {
public:
    Item();
    Item(const std::string& name, ItemType type, int power);

    std::string getName() const;
    ItemType getType() const;
    int getPower() const;
    std::string getDescription() const;

private:
    std::string name_;
    ItemType type_;
    int power_; 
};

#endif