#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include <memory>
#include <random>
#include "Room.h"
#include "Enemy.h"

class LevelManager {
public:
    LevelManager();

    void loadLevel(int levelNumber);
    std::shared_ptr<Room> getCurrentRoom() const;
    bool canGoToNextLevel() const;  
    void nextLevel();

    int getCurrentLevelNumber() const;

    void addLevel(std::shared_ptr<Room> room);
    void generateEnemiesForLevel(int levelNumber);

private:
    int currentLevel_;
    std::vector<std::shared_ptr<Room>> levels_;

    std::shared_ptr<Room> generateRandomRoom(int levelNumber);
    std::vector<Enemy> generateEnemies(int levelNumber);

    std::mt19937 rng_;
};

#endif
