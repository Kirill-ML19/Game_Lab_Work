#include "gtest/gtest.h"
#include "Player.h"

TEST(PlayerTest, HealIncreasesHealth) {
    Player player;
    player.takeDamage(50);
    EXPECT_LT(player.getHealth(), player.getMaxHealth());

    player.heal(20);
    // Здоровье после урона и лечения с учётом защиты
    int expectedHealthAfterDamage = player.getMaxHealth() - std::max(0, 50 - player.getDefense());
    int expectedHealthAfterHeal = expectedHealthAfterDamage + 20;
    if (expectedHealthAfterHeal > player.getMaxHealth())
        expectedHealthAfterHeal = player.getMaxHealth();

    EXPECT_EQ(player.getHealth(), expectedHealthAfterHeal);
}

TEST(PlayerTest, TakeDamageReducesHealth) {
    Player player;
    int initialHealth = player.getHealth();
    int damage = 25;
    player.takeDamage(damage);
    int expectedHealth = initialHealth - std::max(0, damage - player.getDefense());
    EXPECT_EQ(player.getHealth(), expectedHealth);
}

