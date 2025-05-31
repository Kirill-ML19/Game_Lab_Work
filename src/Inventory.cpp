#include "Inventory.h"
#include <iostream>
#include <algorithm>

void Inventory::addItem(const Item& item) {
    auto it = std::find_if(items_.begin(), items_.end(),
        [&](const InventoryItem& invItem) {
            return invItem.item.getName() == item.getName();
        });

    if (it != items_.end()) {
        it->count++;
    } else {
        items_.emplace_back(item, 1);
    }
}

bool Inventory::removeItem(const std::string& name) {
    auto it = std::find_if(items_.begin(), items_.end(),
        [&](const InventoryItem& invItem) { return invItem.item.getName() == name; });

    if (it != items_.end()) {
        it->count--;
        if (it->count <= 0) {
            items_.erase(it);
        }
        return true;
    }
    return false;
}

void Inventory::listItems() const {
    std::cout << "Inventory:\n";
    if (items_.empty()) {
        std::cout << "  (Empty)\n";
        return;
    }
    for (const auto& invItem : items_) {
        std::cout << " - " << invItem.item.getName()
                  << " x" << invItem.count
                  << " (" << (invItem.item.getType() == ItemType::WEAPON ? "Weapon" :
                              invItem.item.getType() == ItemType::ARMOR ? "Armor" :
                              invItem.item.getType() == ItemType::POTION ? "Potion" : "Other")
                  << ", Power: " << invItem.item.getPower() << ")\n";
    }
}

std::optional<Item> Inventory::getItem(const std::string& name) const {
    auto it = std::find_if(items_.begin(), items_.end(),
        [&](const InventoryItem& invItem) { return invItem.item.getName() == name; });

    if (it != items_.end()) {
        return it->item;
    }
    return std::nullopt;
}

bool Inventory::useItem(const std::string& name) {
    auto it = std::find_if(items_.begin(), items_.end(),
        [&](const InventoryItem& invItem) { return invItem.item.getName() == name; });

    if (it != items_.end() && it->count > 0) {
        it->count--;
        if (it->count <= 0) {
            items_.erase(it);
        }
        return true; 
    }
    return false; 
}
