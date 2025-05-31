#include "gtest/gtest.h"
#include "Inventory.h"
#include "Item.h"

TEST(InventoryTest, AddAndRemoveItem) {
    Inventory inv;
    Item sword("Sword", ItemType::WEAPON, 10);

    inv.addItem(sword);
    auto item = inv.getItem("Sword");
    ASSERT_TRUE(item.has_value());
    EXPECT_EQ(item->getPower(), 10);

    bool removed = inv.removeItem("Sword");
    EXPECT_TRUE(removed);
    item = inv.getItem("Sword");
    EXPECT_FALSE(item.has_value());
}

TEST(InventoryTest, ListItemsEmpty) {
    Inventory inv;
    testing::internal::CaptureStdout();
    inv.listItems();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("(Empty)"), std::string::npos);
}
