#include "gtest/gtest.h"
#include "Player.h"
#include "Enemy.h"
#include "Combat.h"

TEST(CombatTest, CombatEndsWhenEnemyDies) {
    Player player;
    Enemy enemy("WeakEnemy", 10, 1, 0, 10);

    Combat combat(player, enemy);

    enemy.takeDamage(20);
    EXPECT_TRUE(enemy.isDead());

    EXPECT_TRUE(player.getHealth() > 0);
}
