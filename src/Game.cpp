#include "Game.h"
#include "Combat.h"
#include "Utils.h"
#include <iostream>

Game::Game() : map_(10, 10) {
    for (int i = 0; i < 5; ++i) {
        auto room = std::make_shared<Room>();
        room->setSize(10, 10);
        levelManager_.addLevel(room);
    }
    loadLevel(0);

    player_.move(5, 5);
}

void Game::loadLevel(int levelNumber) {
    levelManager_.loadLevel(levelNumber);
    auto room = levelManager_.getCurrentRoom();
    if (!room) return;

    levelManager_.generateEnemiesForLevel(levelNumber);

    map_ = Map(10, 10);
    const auto& enemies = room->getEnemies();
    int idx = 0;
    for (const auto& enemy : enemies) {
        if (idx == 0) map_.setTile(3, 3, 'E');
        else if (idx == 1) map_.setTile(7, 7, 'E');
        else map_.setTile(5, 3 + idx, 'E');
        ++idx;
    }
}

void Game::run() {
    bool running = true;
    while (running && player_.getHealth() > 0) {
        Utils::clearScreen();
        render();
        processInput();
        update();

        if (levelManager_.canGoToNextLevel()) {
            std::cout << "You killed all enemies! Press 'n' to go to next level or any other key to stay.\n";
            char c;
            std::cin >> c;
            if (c == 'n') {
                levelManager_.nextLevel();
                loadLevel(levelManager_.getCurrentLevelNumber());
            }
        }
    }
    gameOver();
}

void Game::processInput() {
    std::cout << "Enter the command (w/a/s/d - movement, i - inventory, q - exit): ";
    char cmd;
    std::cin >> cmd;

    int dx = 0, dy = 0;
    switch (cmd) {
    case 'w': dy = -1; break;
    case 's': dy = 1; break;
    case 'a': dx = -1; break;
    case 'd': dx = 1; break;
    case 'i':
        player_.listInventory();
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    case 'q':
        std::cout << "Quitting the game...\n";
        exit(0);
    default:
        std::cout << "Unknown command.\n";
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

void Game::update() {
    auto room = levelManager_.getCurrentRoom();
    if (!room) return;

    auto& enemies = room->getEnemies();

    for (auto it = enemies.begin(); it != enemies.end();) {
        int ex, ey;
        int idx = std::distance(enemies.begin(), it);
        if (idx == 0) { ex = 3; ey = 3; }
        else if (idx == 1) { ex = 7; ey = 7; }
        else { ex = 5; ey = 3 + idx; }

        if (player_.getX() == ex && player_.getY() == ey) {
            Combat combat(player_, *it);
            combat.start();

            if (it->isDead()) {
                player_.gainXP(it->getXPReward());

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
