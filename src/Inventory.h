#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <vector>
#include <optional>

struct InventoryItem {
    Item item;
    int count;

    InventoryItem(const Item& item, int count = 1)
        : item(item), count(count) {}
};

class Inventory {
public:
    void addItem(const Item& item);
    bool removeItem(const std::string& name); 
    void listItems() const;
    std::optional<Item> getItem(const std::string& name) const;
    bool useItem(const std::string& name); 

private:
    std::vector<InventoryItem> items_;
};

#endif 
