#include "SaveSystem.h"
#include <fstream>
#include <iostream>

bool SaveSystem::saveGame(const std::string& filename, const Player& player, const LevelManager& levelManager) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for saving\n";
        return false;
    }

    int x = player.getX();
    int y = player.getY();
    int health = player.getHealth();
    int xp = player.getXP();
    int level = levelManager.getCurrentLevelNumber();

    file.write(reinterpret_cast<const char*>(&x), sizeof(x));
    file.write(reinterpret_cast<const char*>(&y), sizeof(y));
    file.write(reinterpret_cast<const char*>(&health), sizeof(health));
    file.write(reinterpret_cast<const char*>(&xp), sizeof(xp));
    file.write(reinterpret_cast<const char*>(&level), sizeof(level));

    file.close();
    return true;
}

bool SaveSystem::loadGame(const std::string& filename, Player& player, LevelManager& levelManager) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for download\n";
        return false;
    }

    int x, y, health, xp, level;
    file.read(reinterpret_cast<char*>(&x), sizeof(x));
    file.read(reinterpret_cast<char*>(&y), sizeof(y));
    file.read(reinterpret_cast<char*>(&health), sizeof(health));
    file.read(reinterpret_cast<char*>(&xp), sizeof(xp));
    file.read(reinterpret_cast<char*>(&level), sizeof(level));

    player.setPosition(x, y);
    player.setHealth(health);
    player.setXP(xp);
    levelManager.loadLevel(level);

    file.close();
    return true;
}
