#pragma once
#include "ECS.h"
#include "Components.h"
class HealthComponent : public Component
{
public:
    int maxHealth;
    int currentHealth;
    SpriteComponent* sprite;

    bool isDead = false;
    bool dieAnimationPlayed = false;

    HealthComponent() : maxHealth(100), currentHealth(100) {}

    HealthComponent(int maxHealth) : maxHealth(maxHealth), currentHealth(maxHealth) {}

    void init() override
    {
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override 
    {
        if (currentHealth <= 0)
        {
            sprite->Play("Dead");
        }
        if (currentHealth > maxHealth) 
        {
            currentHealth = maxHealth;
        }
    }

    void takeDamage(int damage)
    {
        currentHealth -= damage;
    }

    void heal(int amount)
    {
        currentHealth += amount;
    }
};