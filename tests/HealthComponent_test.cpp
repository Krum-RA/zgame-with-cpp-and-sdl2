#include"UnitTest++\UnitTest++.h"
#include "Components.h"

SUITE(HealthComponentTests)
{
    TEST(DefaultConstructor)
    {
        // Arrange
        HealthComponent health;

        // Assert
        CHECK_EQUAL(100, health.maxHealth);
        CHECK_EQUAL(100, health.currentHealth);
        CHECK(!health.isDead);
        CHECK(!health.dieAnimationPlayed);
    }

    TEST(ParameterizedConstructor)
    {
        // Arrange
        HealthComponent health(150);

        // Assert
        CHECK_EQUAL(150, health.maxHealth);
        CHECK_EQUAL(150, health.currentHealth);
        CHECK(!health.isDead);
        CHECK(!health.dieAnimationPlayed);
    }

    TEST(TakeDamage)
    {
        // Arrange
        HealthComponent health;

        // Act
        health.takeDamage(20);

        // Assert
        CHECK_EQUAL(80, health.currentHealth);
    }

    TEST(Heal)
    {
        // Arrange
        HealthComponent health;
        health.currentHealth = 50;

        // Act
        health.heal(30);

        // Assert
        CHECK_EQUAL(80, health.currentHealth);
    }

    TEST(UpdateMaxHealth)
    {
        // Arrange
        HealthComponent health;

        // Act
        health.heal(100);
        health.update();
        // Assert
        CHECK_EQUAL(100, health.currentHealth);
    }
}
