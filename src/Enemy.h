#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    Enemy(std::string name, int health, int attack, int defense, int xpReward);

    std::string getName() const;
    int getHealth() const;
    void takeDamage(int dmg);
    int getAttack() const;
    int getDefense() const;
    int getXPReward() const;
    bool isDead() const;

private:
    std::string name_;
    int health_;
    int maxHealth_;
    int attack_;
    int defense_;
    int xpReward_;
};

#endif 
