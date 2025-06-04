#include "Combat.h"
#include "Utils.h"
#include <iostream>
#include <random>
#include <chrono>
#include <limits>

Combat::Combat(Player& player, Enemy& enemy)
    : player_(player), enemy_(enemy) {}

void Combat::start() {
    std::cout << "Combat with " << enemy_.getName() << "!\n";
    std::cout << "Your HP: " << player_.getHealth() << "/" << player_.getMaxHealth() << "\n";
    std::cout << "Enemy HP: " << enemy_.getHealth() << "\n\n";
    
    while (!isCombatOver()) {
        playerTurn();
        if (isCombatOver()) break;
        enemyTurn();
    }
    
    if (enemy_.isDead()) {
        std::cout << "You defeated " << enemy_.getName() << " and gained " << enemy_.getXPReward() << " XP!\n";
        player_.gainXP(enemy_.getXPReward());
    } else {
        std::cout << "You were defeated...\n";
    }
    Utils::wait(2000);
}

void Combat::playerTurn() {
    std::cout << "Your turn: (a)ttack, (i)tem, (f)lee: ";
    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (choice == 'a') {
        int dmg = player_.getAttackPower();
        enemy_.takeDamage(dmg);
        std::cout << "You dealt " << dmg << " damage! ";
        std::cout << enemy_.getName() << " HP: " << enemy_.getHealth() << "\n";
    } 
    else if (choice == 'i') {
        useItemInCombat();
    }
    else if (choice == 'f') {
        static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> fleeChance(0, 99);
            
        if (fleeChance(rng) < 50) {
            std::cout << "You escaped successfully!\n";
            player_.heal(player_.getMaxHealth() / 4); 
            enemy_.takeDamage(enemy_.getHealth()); 
        } else {
            std::cout << "Escape failed!\n";
        }
    }
    else {
        std::cout << "Invalid choice! Turn skipped.\n";
    }
}

void Combat::useItemInCombat() {
    const auto& inventory = player_.getInventory().getItems();
    if (inventory.empty()) {
        std::cout << "Inventory is empty!\n";
        return;
    }

    std::cout << "Available items:\n";
    int index = 1;
    for (const auto& item : inventory) {
        if (item.item.getType() == ItemType::HEALTH_POTION ||
            item.item.getType() == ItemType::STRENGTH_POTION ||
            item.item.getType() == ItemType::DEFENSE_POTION) {
            
            std::cout << index << ". " << item.item.getName() 
                      << " x" << item.count 
                      << " - " << item.item.getDescription() << "\n";
        }
        index++;
    }

    std::cout << "0. Cancel\n";
    std::cout << "Select item: ";
    int choice;
    std::cin >> choice;
    
    if (choice > 0) {
        int validIndex = 0;
        for (const auto& item : inventory) {
            if (item.item.getType() == ItemType::HEALTH_POTION ||
                item.item.getType() == ItemType::STRENGTH_POTION ||
                item.item.getType() == ItemType::DEFENSE_POTION) {
                
                validIndex++;
                if (validIndex == choice) {
                    player_.useItem(item.item.getName());
                    return;
                }
            }
        }
    }
    
    std::cout << "Item not used.\n";
}

void Combat::enemyTurn() {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> attackChance(0, 99);

    if (attackChance(rng) < 70) {
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
