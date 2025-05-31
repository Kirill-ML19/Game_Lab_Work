#include "Enemy.h"

Enemy::Enemy(std::string name, int health, int attack, int defense, int xpReward)
    : name_(std::move(name)), health_(health), maxHealth_(health),
      attack_(attack), defense_(defense), xpReward_(xpReward) {}

std::string Enemy::getName() const {
    return name_;
}

int Enemy::getHealth() const {
    return health_;
}

void Enemy::takeDamage(int dmg) {
    int damageTaken = dmg - defense_;
    if (damageTaken < 0) damageTaken = 0;
    health_ -= damageTaken;
    if (health_ < 0) health_ = 0;
}

int Enemy::getAttack() const {
    return attack_;
}

int Enemy::getDefense() const {
    return defense_;
}

int Enemy::getXPReward() const {
    return xpReward_;
}

bool Enemy::isDead() const {
    return health_ <= 0;
}
