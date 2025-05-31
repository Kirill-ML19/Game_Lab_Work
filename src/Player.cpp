#include "Player.h"
#include <iostream>

Player::Player()
    : x_(0), y_(0), health_(100), maxHealth_(100),
      level_(1), xp_(0), xpToNextLevel_(100),
      equippedWeapon_("Hands", ItemType::WEAPON, 5),
      equippedArmor_("Regular clothes", ItemType::ARMOR, 2)
{}

void Player::draw() const {
    std::cout << "Player: (" << x_ << ", " << y_ << ") Health: " << health_ << "/" << maxHealth_
              << " Level: " << level_ << " XP: " << xp_ << "/" << xpToNextLevel_
              << "\n Weapon: " << equippedWeapon_.getName() << " (Damage: " << equippedWeapon_.getPower() << ")"
              << "\n Armor: " << equippedArmor_.getName() << " (Protection: " << equippedArmor_.getPower() << ")\n";
}

void Player::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}

int Player::getX() const { return x_; }
int Player::getY() const { return y_; }

int Player::getHealth() const { return health_; }
int Player::getMaxHealth() const { return maxHealth_; }  

void Player::takeDamage(int dmg) {
    int damageTaken = dmg - getDefense();
    if (damageTaken < 0) damageTaken = 0;
    health_ -= damageTaken;
    if (health_ < 0) health_ = 0;
}

void Player::heal(int amount) {
    health_ += amount;
    if (health_ > maxHealth_) health_ = maxHealth_;
}

int Player::getLevel() const { return level_; }

void Player::gainXP(int xp) {
    xp_ += xp;
    while (xp_ >= xpToNextLevel_) {
        xp_ -= xpToNextLevel_;
        level_++;
        xpToNextLevel_ = static_cast<int>(xpToNextLevel_ * 1.5);

        maxHealth_ += 20;
        health_ = maxHealth_;

        std::cout << "You've leveled up! You now have level " << level_ << " and health " << maxHealth_ << ".\n";
    }
}

int Player::getXP() const { return xp_; }
int Player::getXPToNextLevel() const { return xpToNextLevel_; }

void Player::equipWeapon(const Item& weapon) {
    if (weapon.getType() == ItemType::WEAPON) {
        equippedWeapon_ = weapon;
        std::cout << "You have equipped a weapon: " << weapon.getName() << "\n";
    }
}

void Player::equipArmor(const Item& armor) {
    if (armor.getType() == ItemType::ARMOR) {
        equippedArmor_ = armor;
        std::cout << "You have equipped the armor: " << armor.getName() << "\n";
    }
}

int Player::getAttackPower() const {
    return equippedWeapon_.getPower() + level_ * 2;
}

int Player::getDefense() const {
    return equippedArmor_.getPower() + level_;
}

void Player::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Player::setHealth(int health) {
    health_ = health;
    if (health_ > maxHealth_) health_ = maxHealth_;
    if (health_ < 0) health_ = 0;
}

void Player::setXP(int xp) {
    xp_ = xp;
}

void Player::addItemToInventory(const Item& item) {
    inventory_.addItem(item);
}

void Player::listInventory() const {
    inventory_.listItems();
}

bool Player::usePotion() {
    auto potionOpt = inventory_.getItem("Health Potion");
    if (!potionOpt) {
        std::cout << "You don't have any Health Potions!\n";
        return false;
    }
    if (inventory_.useItem("Health Potion")) {
        heal(50);
        std::cout << "You used a Health Potion and restored 50 health.\n";
        return true;
    }
    return false;
}
