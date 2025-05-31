#ifndef ROOM_H
#define ROOM_H

#include "Map.h"
#include "Enemy.h"
#include <vector>
#include <utility>

class Room {
public:
    Room(int width = 10, int height = 10);

    void setSize(int width, int height);

    void addEnemy(const Enemy& enemy, int x, int y);
    void removeEnemyAt(int x, int y);
    bool isEnemyAt(int x, int y) const;

    const std::vector<Enemy>& getEnemies() const;
    std::vector<Enemy>& getEnemies();

    void setEnemies(const std::vector<Enemy>& enemies);

    Map& getMap();
    const Map& getMap() const;

    void draw() const;

private:
    Map map_;
    std::vector<Enemy> enemies_;
    std::vector<std::pair<int,int>> enemyPositions_;
};

#endif
