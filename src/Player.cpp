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
              << "\nWeapon: " << equippedWeapon_.getName() << " (ATK +" << equippedWeapon_.getPower() << ")"
              << "\nArmor: " << equippedArmor_.getName() << " (DEF +" << equippedArmor_.getPower() << ")";
    
    if (attackBuff_ > 0) {
        std::cout << "\nAttack Buff: +" << attackBuff_ << " (" << attackBuffDuration_ << " turns)";
    }
    if (defenseBuff_ > 0) {
        std::cout << "\nDefense Buff: +" << defenseBuff_ << " (" << defenseBuffDuration_ << " turns)";
    }
    std::cout << "\n";
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
        if (equippedWeapon_.getName()!="First") {
            addItemToInventory(equippedWeapon_);
        }

        equippedWeapon_=weapon;
        std::cout << "Equipped weapon: " << weapon.getName()  << " (ATK +" << weapon.getPower() << ")\n";
    } else {
        std::cout << "This is not a weapon!\n";
    }
}

void Player::equipArmor(const Item& armor) {
    if (armor.getType() == ItemType::ARMOR) {
        if (equippedArmor_.getName()!="Clothes") {
            addItemToInventory(equippedArmor_);
        }

        equippedArmor_ = armor;
        std::cout << "Equipped armor: " << armor.getName()  << " (DEF +" << armor.getPower() << ")\n";
    } else {
        std::cout << "This is not armor!\n";
    }
}

int Player::getAttackPower() const {
    return equippedWeapon_.getPower() + level_ * 2 + attackBuff_;
}

int Player::getDefense() const {
    return equippedArmor_.getPower() + level_ + defenseBuff_;
}

void Player::useItem(const std::string& name) {
    auto itemOpt = inventory_.getItem(name);
    if (!itemOpt) {
        std::cout << "You don't have a '" << name << "'!\n";
        return;
    }

    Item item = *itemOpt;
    switch(item.getType()) {
        case ItemType::HEALTH_POTION:
            heal(item.getPower());
            inventory_.useItem(name);
            std::cout << "Used " << name << " and healed " << item.getPower() << " HP!\n";
            break;
            
        case ItemType::STRENGTH_POTION:
            addBuff(ItemType::STRENGTH_POTION, item.getPower(), 3);
            inventory_.useItem(name);
            break;
            
        case ItemType::DEFENSE_POTION:
            addBuff(ItemType::DEFENSE_POTION, item.getPower(), 3);
            inventory_.useItem(name);
            break;
            
        case ItemType::WEAPON:
            equipWeapon(item);
            break;
            
        case ItemType::ARMOR:
            equipArmor(item);
            break;
            
        default:
            std::cout << "You can't use this item directly!\n";
    }
}

void Player::addBuff(ItemType type, int power, int duration) {
    switch(type) {
        case ItemType::STRENGTH_POTION:
            attackBuff_ = power;
            attackBuffDuration_ = duration;
            std::cout << "Attack increased by " << power << " for " << duration << " turns!\n";
            break;
            
        case ItemType::DEFENSE_POTION:
            defenseBuff_ = power;
            defenseBuffDuration_ = duration;
            std::cout << "Defense increased by " << power << " for " << duration << " turns!\n";
            break;
            
        default:
            break;
    }
}

void Player::updateBuffs() {
    if (attackBuffDuration_ > 0) {
        attackBuffDuration_--;
        if (attackBuffDuration_ == 0) {
            std::cout << "Your attack buff expired!\n";
            attackBuff_ = 0;
        }
    }
    
    if (defenseBuffDuration_ > 0) {
        defenseBuffDuration_--;
        if (defenseBuffDuration_ == 0) {
            std::cout << "Your defense buff expired!\n";
            defenseBuff_ = 0;
        }
    }
}

int Player::getBaseAttack() const {
    return equippedWeapon_.getPower() + level_ * 2;
}

int Player::getBaseDefense() const {
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
        int healAmount = potionOpt->getPower();
        std::cout << "You used a Health Potion and restored 50 health.\n";
        return true;
    }
    return false;
}

const Inventory& Player::getInventory() const {
    return inventory_;
}

Item Player::getEquippedWeapon() const {
    return equippedWeapon_;
}

Item Player::getEquippedArmor() const {
    return equippedArmor_;
}

void Player::setMaxHealth(int newMaxHealth) {
    maxHealth_ = newMaxHealth;
}

void Player::setLevel(int newLevel) {
    level_ = newLevel;
}

void Player::setXPToNextLevel(int newXPToNext) {
    xpToNextLevel_ = newXPToNext;
}

void Player::clearInventory() {
    inventory_=Inventory();
    equippedWeapon_=Item("Hands",ItemType::WEAPON, 5);
    equippedArmor_=Item("Regular clothes", ItemType::ARMOR, 2);
}

void Player::showStats() const {
    std::cout << "\n--- Character Stats ---\n";
    std::cout << "Level: " << level_ << "\n";
    std::cout << "XP: " << xp_ << " / " << xpToNextLevel_ << "\n";
    std::cout << "Health: " << health_ << " / " << maxHealth_ << "\n";
    std::cout << "-----------------------\n";
    std::cout << "Weapon: " << equippedWeapon_.getName() << " (+" << getAttackPower() << " Attack)\n";
    std::cout << "Armor: " << equippedArmor_.getName() << " (+" << getDefense() << " Defense)\n";
    std::cout << "-----------------------\n\n";
}

