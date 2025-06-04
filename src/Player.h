#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Item.h"
#include "Inventory.h"

class Player {
public:
    Player();

    void draw() const;
    void move(int dx, int dy);
    int getX() const;
    int getY() const;
    int getHealth() const;
    int getMaxHealth() const;
    void takeDamage(int dmg);
    void heal(int amount);
    int getLevel() const;
    void gainXP(int xp);
    int getXP() const;
    int getXPToNextLevel() const;
    void equipWeapon(const Item& weapon);
    void equipArmor(const Item& armor);
    int getAttackPower() const;
    int getDefense() const;
    void setPosition(int x, int y);
    void setHealth(int health);
    void setXP(int xp);
    void addItemToInventory(const Item& item);
    void listInventory() const;
    bool usePotion();
    const Inventory& getInventory() const;
    Item getEquippedWeapon() const;
    Item getEquippedArmor() const;
    void setMaxHealth(int newMaxHealth);
    void setLevel(int newLevel);
    void setXPToNextLevel(int newXPToNext);
    void clearInventory();
    void showStats() const;
    void useItem(const std::string& name);
    void updateBuffs();
    int getBaseAttack() const;
    int getBaseDefense() const;
    void addBuff(ItemType type, int power, int duration);

private:
    int x_, y_;
    int health_, maxHealth_;
    int level_;
    int xp_;
    int xpToNextLevel_;
    Item equippedWeapon_;
    Item equippedArmor_;
    Inventory inventory_;
    
    int attackBuff_ = 0;
    int defenseBuff_ = 0;
    int attackBuffDuration_ = 0;
    int defenseBuffDuration_ = 0;
};

#endif