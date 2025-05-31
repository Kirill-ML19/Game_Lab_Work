#include "gtest/gtest.h"
#include "Enemy.h"

TEST(EnemyTest, TakeDamageRespectsDefense) {
    Enemy enemy("TestEnemy", 100, 10, 5, 50);
    enemy.takeDamage(3);  
    EXPECT_EQ(enemy.getHealth(), 100);

    enemy.takeDamage(10); 
    EXPECT_EQ(enemy.getHealth(), 95);

    enemy.takeDamage(200); 
    EXPECT_EQ(enemy.getHealth(), 0);
    EXPECT_TRUE(enemy.isDead());
}
