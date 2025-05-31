#include "Item.h"

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
