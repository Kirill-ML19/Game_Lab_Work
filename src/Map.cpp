#include "Map.h"
#include <iostream>

Map::Map(int width, int height)
    : width_(width), height_(height), tiles_(height, std::string(width, '.')) {}

void Map::draw() const {
    for (const auto& row : tiles_) {
        std::cout << row << '\n';
    }
}

bool Map::isWalkable(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_)
        return false;
    char c = tiles_[y][x];
    return c == '.' || c == 'P' || c == 'E' || c == 'C'; 
}

char Map::getTile(int x, int y) const {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        return tiles_[y][x];
    }
    return '#';
}

void Map::setTile(int x, int y, char symbol) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        tiles_[y][x] = symbol;
    }
}

void Map::clear() {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            tiles_[y][x] = '.';  
        }
    }
}

int Map::getWidth() const { return width_; }
int Map::getHeight() const { return height_; }
