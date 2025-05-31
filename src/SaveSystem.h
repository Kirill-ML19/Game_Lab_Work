#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <string>
#include "Player.h"
#include "LevelManager.h"

class SaveSystem {
public:
    static bool saveGame(const std::string& filename, const Player& player, const LevelManager& levelManager);
    static bool loadGame(const std::string& filename, Player& player, LevelManager& levelManager);
};

#endif 
