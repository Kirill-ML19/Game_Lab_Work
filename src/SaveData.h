#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <string>
#include <vector>
#include "Item.h"

struct ItemData {
    char name[50];
    ItemType type;
    int power;
    int count;
};

struct PlayerData {
    int x;
    int y;
    int health;
    int maxHealth;
    int level;
    int xp;
    int xpToNextLevel;
    char equippedWeaponName[50];
    char equippedArmorName[50];
};

#endif 