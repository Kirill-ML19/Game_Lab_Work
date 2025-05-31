#ifndef COMBAT_H
#define COMBAT_H

#include "Player.h"
#include "Enemy.h"

class Combat {
public:
    Combat(Player& player, Enemy& enemy);

    void start();

private:
    Player& player_;
    Enemy& enemy_;

    void playerTurn();
    void enemyTurn();
    bool isCombatOver() const;
};

#endif
