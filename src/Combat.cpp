#include "Combat.h"
#include <iostream>

Combat::Combat(Player& player, Enemy& enemy)
    : player_(player), enemy_(enemy) {}

void Combat::start() {
    std::cout << "The fight began with the enemy: " << enemy_.getName() << "!\n";

    while (!isCombatOver()) {
        playerTurn();
        if (isCombatOver()) break;
        enemyTurn();
    }

    if (enemy_.isDead()) {
        std::cout << "You have defeated the enemy " << enemy_.getName() << " and received "
                  << enemy_.getXPReward() << " XP!\n";
        player_.gainXP(enemy_.getXPReward());
    } else {
        std::cout << "You lost the fight...\n";
    }
}

void Combat::playerTurn() {
    std::cout << "Your move: attack (a) or use potion (h)? ";
    char choice;
    std::cin >> choice;

    if (choice == 'a') {
        int dmg = player_.getAttackPower();
        enemy_.takeDamage(dmg);
        std::cout << "You dealt " << dmg << " damage to the enemy. Enemy health: "
                  << enemy_.getHealth() << "\n";
    } else if (choice == 'h') {
        if (!player_.usePotion()) {
            std::cout << "No potions left, turn skipped.\n";
        } else {
            std::cout << "You used a potion. Your health: " << player_.getHealth() << "\n";
        }
    } else {
        std::cout << "Incorrect choice, move missed.\n";
    }
}

void Combat::enemyTurn() {
    int attackChance = rand() % 100;
    if (attackChance < 70) {
        int dmg = enemy_.getAttack();
        player_.takeDamage(dmg);
        std::cout << "The enemy attacks and deals " << dmg << " damage. Your health: "
                  << player_.getHealth() << "\n";
    } else {
        std::cout << "The enemy hesitates and misses the turn.\n";
    }
}

bool Combat::isCombatOver() const {
    return player_.getHealth() <= 0 || enemy_.isDead();
}
