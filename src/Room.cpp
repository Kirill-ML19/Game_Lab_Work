#include "Room.h"
#include <iostream>

Room::Room(int width, int height)
    : map_(width, height) {}

void Room::setSize(int width, int height) {
    map_ = Map(width, height);
    enemies_.clear();
    enemyPositions_.clear();
}

void Room::addEnemy(const Enemy& enemy, int x, int y) {
    enemies_.push_back(enemy);
    enemyPositions_.push_back({x, y});
    map_.setTile(x, y, 'E');
}

void Room::removeEnemyAt(int x, int y) {
    for (size_t i = 0; i < enemyPositions_.size(); ++i) {
        if (enemyPositions_[i].first == x && enemyPositions_[i].second == y) {
            enemies_.erase(enemies_.begin() + i);
            enemyPositions_.erase(enemyPositions_.begin() + i);
            map_.setTile(x, y, '.');
            break;
        }
    }
}

bool Room::isEnemyAt(int x, int y) const {
    for (const auto& pos : enemyPositions_) {
        if (pos.first == x && pos.second == y)
            return true;
    }
    return false;
}

const std::vector<Enemy>& Room::getEnemies() const {
    return enemies_;
}

std::vector<Enemy>& Room::getEnemies() {
    return enemies_;
}

void Room::setEnemies(const std::vector<Enemy>& enemies) {
    enemies_ = enemies;
    enemyPositions_.clear();

    map_.clear(); 
    for (size_t i = 0; i < enemies_.size(); ++i) {
        int x = static_cast<int>(i);
        int y = static_cast<int>(i);
        if (x < map_.getWidth() && y < map_.getHeight()) {
            enemyPositions_.emplace_back(x, y);
            map_.setTile(x, y, 'E');
        }
    }
}

Map& Room::getMap() {
    return map_;
}

const Map& Room::getMap() const {
    return map_;
}

void Room::draw() const {
    map_.draw();
}
