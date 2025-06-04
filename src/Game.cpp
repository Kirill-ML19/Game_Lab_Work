#include "Game.h"
#include "Combat.h"
#include "Utils.h"
#include "Map.h"
#include <iostream>
#include <limits>
#include <random>
#include <chrono>
#include <algorithm>

Game::Game() : map_(10, 10) {
    for (int i = 0; i < 5; ++i) {
        auto room = std::make_shared<Room>();
        room->setSize(10, 10);
        levelManager_.addLevel(room);
    }
    loadLevel(0);

    player_.move(5, 5);
}

void Game::openChest(int x, int y) {
    Utils::clearScreen();
    render(); 
    std::cout << "You found a chest!\n";

    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> lootType(0, 99);
    
    if (lootType(rng) < 60) {
        Item potion("Health Potion", ItemType::HEALTH_POTION, 50);
        player_.addItemToInventory(potion);
        player_.addItemToInventory(potion);
        std::cout << "You found two Health Potions!\n";
    } else {
        int level = levelManager_.getCurrentLevelNumber();
        Item epicWeapon("Fine Steel Sword", ItemType::WEAPON, 10 + 3 * level);
        player_.addItemToInventory(epicWeapon);
        std::cout << "You found a Fine Steel Sword!\n";
    }

    map_.setTile(x, y, '.');
    chestPositions_.erase(std::remove_if(chestPositions_.begin(), chestPositions_.end(),
        [x, y](const std::pair<int, int>& pos) {
            return pos.first == x && pos.second == y;
        }), chestPositions_.end());

    std::cout << "Press Enter to continue...";
    std::cin.get();
}

void Game::loadLevel(int levelNumber) {
    levelManager_.loadLevel(levelNumber);
    auto room = levelManager_.getCurrentRoom();
    if (!room) return;

    levelManager_.generateEnemiesForLevel(levelNumber);

    map_ = Map(10, 10);
    const auto& enemies = room->getEnemies();

    const int playerStartX=5;
    const int playerStartY=5;

    int idx = 0;
    for (const auto& enemy : enemies) {
        int ex, ey;
        if (idx == 0) { ex=3; ey=3; }
        else if (idx == 1) { ex=7; ey=7;}
        else { ex=5; ey=3+idx; };

        if (ex==playerStartX && ey==playerStartY) {
            ey++;
        }
        map_.setTile(ex, ey, 'E');
        ++idx;
    }

    chestPositions_.clear();
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> chestCount(1, 2); 
    
    for (int i = 0; i < chestCount(rng); ++i) {
        int cx, cy;
        while (true) {
            std::uniform_int_distribution<int> posDist(0, 9);
            cx = posDist(rng);
            cy = posDist(rng);
            if (map_.isWalkable(cx, cy) && map_.getTile(cx, cy) == '.') {
                 break;
            }
        }
        map_.setTile(cx, cy, 'C');  
        chestPositions_.push_back({cx, cy});
    }
}

void Game::run() {
    bool running = true;
    while (running && player_.getHealth() > 0) {
        Utils::clearScreen();
        render();
        processInput();
        update();

        if (levelManager_.getCurrentRoom()->getEnemies().empty()) {
            std::cout << "You killed all enemies! Press 'n' to go to next level or any other key to stay.\n";
            char c;
            std::cin >> c;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (c == 'n') {
                levelManager_.nextLevel();
                loadLevel(levelManager_.getCurrentLevelNumber());
            }
        }
    }
    gameOver();
}

void Game::processInput() {
    std::cout << "Enter the command (w/a/s/d - movement, i - inventory, e - equip, u - use, c - stats, q - exit): ";
    char cmd;
    std::cin >> cmd;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    int dx = 0, dy = 0;
    switch (cmd) {
    case 'w': dy = -1; break;
    case 's': dy = 1; break;
    case 'a': dx = -1; break;
    case 'd': dx = 1; break;
    case 'i':
        manageInventory();
        return;
    case 'e':
        showEquipment();
        return;
    case 'u':
        useItem();
        return;
    case 'c':
        player_.showStats();
        std::cout << "Press Enter to continue...";
        std::cin.get();
        return;
    case 'q':
        std::cout << "Quitting the game...\n";
        exit(0);
    default:
        std::cout << "Unknown command.\n";
        Utils::wait(1000);
        return;
    }

    int newX = player_.getX() + dx;
    int newY = player_.getY() + dy;

    if (map_.isWalkable(newX, newY)) {
        player_.move(dx, dy);
    } else {
        std::cout << "You can't go there!\n";
        Utils::wait(1000);
    }
}

void Game::manageInventory() {
    Utils::clearScreen();
    player_.listInventory();
    
    std::cout << "\nCommands:\n";
    std::cout << "e [num] - Equip weapon/armor\n";
    std::cout << "u [num] - Use item\n";
    std::cout << "x - Exit inventory\n";
    std::cout << "> ";
    
    char cmd;
    std::cin >> cmd;
    
    if (cmd == 'e' || cmd == 'u') {
        int index;
        std::cin >> index;
        
        const auto& items = player_.getInventory().getItems();
        if (index > 0 && index <= items.size()) {
            Item item = items[index-1].item;
            
            if (cmd == 'e') {
                if (item.getType() == ItemType::WEAPON) {
                    player_.equipWeapon(item);
                } 
                else if (item.getType() == ItemType::ARMOR) {
                    player_.equipArmor(item);
                }
                else {
                    std::cout << "You can't equip that!\n";
                    Utils::wait(1500);
                }
            }
            else if (cmd == 'u') {
                player_.useItem(item.getName());
                Utils::wait(1500);
            }
        }
    }
}

void Game::showEquipment() {
    Utils::clearScreen();
    player_.showStats();
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

void Game::useItem() {
    Utils::clearScreen();
    player_.listInventory();
    
    if (player_.getInventory().getItems().empty()) {
        std::cout << "Inventory is empty!\n";
        Utils::wait(1500);
        return;
    }
    
    std::cout << "\nEnter item number to use (0 to cancel): ";
    int choice;
    std::cin >> choice;
    
    if (choice > 0) {
        const auto& items = player_.getInventory().getItems();
        if (choice <= items.size()) {
            player_.useItem(items[choice-1].item.getName());
        }
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Utils::wait(1500);
}

void Game::generateLoot(const Enemy& enemy) {

    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dropChance(0, 99);

    if (dropChance(rng) < 40) {
        std::uniform_int_distribution<int> lootType(0, 99);
        int typeRoll = lootType(rng);

        if (typeRoll < 60) {
            Item potion("Health Potion", ItemType::HEALTH_POTION, 50); 
            player_.addItemToInventory(potion);
            std::cout << enemy.getName() << " dropped a Health Potion!\n";
        } else  if (typeRoll <  85) {
            Item potion("Strength Potion", ItemType::STRENGTH_POTION, 3 + levelManager_.getCurrentLevelNumber());
            player_.addItemToInventory(potion);
            std::cout << enemy.getName() << " dropped a Strength Potion!\n";
        } else if (typeRoll < 95) {
            Item potion("Defense Potion", ItemType::DEFENSE_POTION, 2 + levelManager_.getCurrentLevelNumber());
            player_.addItemToInventory(potion);
            std::cout << enemy.getName() << " dropped a Defense Potion!\n";
        } else {
            int level = levelManager_.getCurrentLevelNumber();
            if (typeRoll % 2 == 0) {
                Item weapon("Steel Sword", ItemType::WEAPON, 10 + 2 * level);
                player_.addItemToInventory(weapon);
                std::cout << enemy.getName() << " dropped a Steel Sword!\n";
            } else {
                Item armor("Chainmail", ItemType::ARMOR, 8 + level);
                player_.addItemToInventory(armor);
                std::cout << enemy.getName() << " dropped a Chainmail Armor!\n";
            }
        }
    }
}

void Game::update() {
    player_.updateBuffs();
    auto room = levelManager_.getCurrentRoom();
    if (!room) return;

    auto& enemies = room->getEnemies();

    for (auto it = enemies.begin(); it != enemies.end();) {
        int ex, ey;
        int idx = std::distance(enemies.begin(), it);
        if (idx == 0) { ex = 3; ey = 3; }
        else if (idx == 1) { ex = 7; ey = 7; }
        else { ex = 5; ey = 3 + idx; if (ex==5 && ey==5) ey++;}

        if (player_.getX() == ex && player_.getY() == ey) {
            Combat combat(player_, *it);
            combat.start();

            if (it->isDead()) {
                generateLoot(*it);
                it = enemies.erase(it);
                map_.setTile(ex, ey, '.');
            } else {
                ++it;
            }
            return; 
        } else {
            ++it;
        }
    }

    for (const auto& pos : chestPositions_) {
        if (player_.getX() == pos.first && player_.getY() == pos.second) {
            openChest(pos.first, pos.second);
            return; 
        }
    }
}

void Game::render() const {
    Map tempMap = map_;
    tempMap.setTile(player_.getX(), player_.getY(), 'P');
    tempMap.draw();

    player_.draw();
}

void Game::gameOver() const {
    if (player_.getHealth() <= 0) {
        std::cout << "You lost... Game over.\n";
    } else {
        std::cout << "Game over.\n";
    }
}
