#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Map.h"
#include "Inventory.h"
#include "Enemy.h"
#include "LevelManager.h"
#include <vector>
#include <memory>
#include <utility>

class Game {
public:
    Game();
    void run();
    void useItem();
private:
    Player player_;
    Map map_;
    Inventory inventory_;
    LevelManager levelManager_;
    std::vector<std::pair<int,int>> chestPositions_;

    void processInput();
    void update();
    void render() const;
    void gameOver() const;
    void loadLevel(int levelNumber);
    void generateLoot(const Enemy& enemy);
    void openChest(int x, int y);
    void showEquipment();
    void manageInventory();
};

#endif
