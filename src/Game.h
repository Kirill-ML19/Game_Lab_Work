#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Map.h"
#include "Inventory.h"
#include "Enemy.h"
#include "LevelManager.h"
#include <vector>
#include <memory>

class Game {
public:
    Game();
    void run();

private:
    Player player_;
    Map map_;
    Inventory inventory_;
    LevelManager levelManager_;

    void processInput();
    void update();
    void render() const;
    void gameOver() const;

    void loadLevel(int levelNumber);
};

#endif
