#include "SaveSystem.h"
#include "SaveData.h"      
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>        

bool SaveSystem::saveGame(const std::string& filename, const Player& player, const LevelManager& levelManager) {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "Error opening file for saving\n";
        return false;
    }

    PlayerData pd;
    pd.x = player.getX();
    pd.y = player.getY();
    pd.health = player.getHealth();
    pd.maxHealth = player.getMaxHealth();
    pd.level = player.getLevel();
    pd.xp = player.getXP();
    pd.xpToNextLevel = player.getXPToNextLevel();
    
    strncpy(pd.equippedWeaponName, player.getEquippedWeapon().getName().c_str(), 49);
    pd.equippedWeaponName[49] = '\0';
    strncpy(pd.equippedArmorName, player.getEquippedArmor().getName().c_str(), 49);
    pd.equippedArmorName[49] = '\0';
    
    file.write(reinterpret_cast<const char*>(&pd), sizeof(PlayerData));

    const auto& inventoryItems = player.getInventory().getItems();
    size_t itemCount = inventoryItems.size();
    file.write(reinterpret_cast<const char*>(&itemCount), sizeof(itemCount));

    for (const auto& invItem : inventoryItems) {
        ItemData id;
        strncpy(id.name, invItem.item.getName().c_str(), 49);
        id.name[49] = '\0';
        id.type = invItem.item.getType();
        id.power = invItem.item.getPower();
        id.count = invItem.count;
        file.write(reinterpret_cast<const char*>(&id), sizeof(ItemData));
    }

    int currentLevel = levelManager.getCurrentLevelNumber();
    file.write(reinterpret_cast<const char*>(&currentLevel), sizeof(currentLevel));

    file.close();
    std::cout << "Game saved successfully!\n";
    return true;
}

bool SaveSystem::loadGame(const std::string& filename, Player& player, LevelManager& levelManager) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for loading\n";
        return false;
    }

    PlayerData pd;
    file.read(reinterpret_cast<char*>(&pd), sizeof(PlayerData));
    if (file.gcount() != sizeof(PlayerData)) return false; 

    player.setPosition(pd.x, pd.y);
    player.setMaxHealth(pd.maxHealth);
    player.setHealth(pd.health);
    player.setLevel(pd.level);
    player.setXP(pd.xp);
    player.setXPToNextLevel(pd.xpToNextLevel);

    player.clearInventory();
    
    size_t itemCount;
    file.read(reinterpret_cast<char*>(&itemCount), sizeof(itemCount));
    if (file.gcount() != sizeof(itemCount)) return false;

    for (size_t i = 0; i < itemCount; ++i) {
        ItemData id;
        file.read(reinterpret_cast<char*>(&id), sizeof(ItemData));
        if (file.gcount() != sizeof(ItemData)) return false;

        Item item(id.name, id.type, id.power);
        for (int c = 0; c < id.count; ++c) {
            player.addItemToInventory(item);
        }
    }

    auto weaponOpt = player.getInventory().getItem(pd.equippedWeaponName);
    if (weaponOpt) player.equipWeapon(*weaponOpt);

    auto armorOpt = player.getInventory().getItem(pd.equippedArmorName);
    if (armorOpt) player.equipArmor(*armorOpt);

    int currentLevel;
    file.read(reinterpret_cast<char*>(&currentLevel), sizeof(currentLevel));
    if (file.gcount() != sizeof(currentLevel)) return false;
    levelManager.loadLevel(currentLevel);

    file.close();
    std::cout << "Game loaded successfully!\n";
    return true;
}