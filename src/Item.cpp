#include "Item.h"
#include <sstream>

Item::Item() : name_(""), type_(ItemType::MISC), power_(0) {}

Item::Item(const std::string& name, ItemType type, int power)
    : name_(name), type_(type), power_(power) {}

std::string Item::getName() const {
    return name_;
}

ItemType Item::getType() const {
    return type_;
}

int Item::getPower() const {
    return power_;
}

std::string Item::getDescription() const {
    std::ostringstream oss;
    switch(type_) {
        case ItemType::WEAPON:
            oss << "Weapon (ATK +" << power_ << ")";
            break;
        case ItemType::ARMOR:
            oss << "Armor (DEF +" << power_ << ")";
            break;
        case ItemType::HEALTH_POTION:
            oss << "Heals " << power_ << " HP";
            break;
        case ItemType::STRENGTH_POTION:
            oss << "+" << power_ << " ATK for 3 turns";
            break;
        case ItemType::DEFENSE_POTION:
            oss << "+" << power_ << " DEF for 3 turns";
            break;
        default:
            oss << "Miscellaneous item";
    }
    return oss.str();
}