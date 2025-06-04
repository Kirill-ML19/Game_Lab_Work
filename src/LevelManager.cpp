#include "LevelManager.h"
#include <ctime>

LevelManager::LevelManager() : currentLevel_(0), rng_(static_cast<unsigned int>(std::time(nullptr))) {}

void LevelManager::loadLevel(int levelNumber) {
    if (levelNumber < 0 || levelNumber >= static_cast<int>(levels_.size())) return;
    currentLevel_ = levelNumber;
}

std::shared_ptr<Room> LevelManager::getCurrentRoom() const {
    if (currentLevel_ < 0 || currentLevel_ >= static_cast<int>(levels_.size()))
        return nullptr;
    return levels_[currentLevel_];
}

bool LevelManager::canGoToNextLevel() const {
    auto room = getCurrentRoom();
    if (!room) return false;

    return room->getEnemies().empty();
}

void LevelManager::nextLevel() {
    if (canGoToNextLevel() && currentLevel_ + 1 < static_cast<int>(levels_.size())) {
        ++currentLevel_;
        generateEnemiesForLevel(currentLevel_);
    }
}

int LevelManager::getCurrentLevelNumber() const {
    return currentLevel_;
}

void LevelManager::addLevel(std::shared_ptr<Room> room) {
    levels_.push_back(room);
}

void LevelManager::generateEnemiesForLevel(int levelNumber) {
    if (levelNumber < 0 || levelNumber >= static_cast<int>(levels_.size())) return;
    auto enemies = generateEnemies(levelNumber);
    levels_[levelNumber]->setEnemies(enemies);
}

std::shared_ptr<Room> LevelManager::generateRandomRoom(int levelNumber) {
    auto room = std::make_shared<Room>();
    room->setSize(10, 10);
    auto enemies = generateEnemies(levelNumber);
    room->setEnemies(enemies);
    return room;
}

std::vector<Enemy> LevelManager::generateEnemies(int levelNumber) {
    std::vector<Enemy> enemies;
    int maxEnemies = std::min(3,1 + levelNumber);
    std::uniform_int_distribution<int> countDist(1, maxEnemies); 
    int enemyCount = (levelNumber==0) ? 1 : countDist(rng_);

    std::vector<std::string> enemyTypes = {"Goblin", "Skeleton", "Orc"};

    std::uniform_int_distribution<int> typeDist(0, static_cast<int>(enemyTypes.size()) - 1);
    std::uniform_int_distribution<int> healthDist(40 + 10*levelNumber, 80 + 20*levelNumber);
    std::uniform_int_distribution<int> attackDist(5 + 2*levelNumber, 15 + 3*levelNumber);
    std::uniform_int_distribution<int> defenseDist(1 + levelNumber, 5 + 2*levelNumber);
    std::uniform_int_distribution<int> xpDist(20 + 10*levelNumber, 50 + 20*levelNumber);

    for (int i = 0; i < enemyCount; ++i) {
        std::string type = enemyTypes[typeDist(rng_)];
        int health = healthDist(rng_);
        int attack = attackDist(rng_);
        int defense = defenseDist(rng_);
        int xp = xpDist(rng_);

        std::uniform_int_distribution<int> eliteChance(0, 99);
        if (eliteChance(rng_) < 20) {
            type = "Elite " + type;
            health = static_cast<int>(health * 1.5);
            attack = static_cast<int>(attack * 1.5);
            xp = static_cast<int>(xp * 2);
        }

        enemies.emplace_back(type, health, attack, defense, xp);
    }

    return enemies;
}
