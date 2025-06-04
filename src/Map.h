#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

class Map {
public:
    Map(int width, int height);

    void draw() const;
    bool isWalkable(int x, int y) const;
    void setTile(int x, int y, char symbol);

    int getWidth() const;
    int getHeight() const;

    void clear();  
    char getTile(int x, int y) const;

private:
    int width_;
    int height_;
    std::vector<std::string> tiles_;
};

#endif
