#include "UnitTest++/UnitTest++.h"
#include "Components.h"
#include "Vector2D.h"
#include "SDL.h"

TEST(TestAIComponent_UpdateChaseState) 
{
    Manager manager;
    Entity& playerEntity = manager.addEntity();
    playerEntity.addComponent<HealthComponent>().currentHealth = 100;
    playerEntity.addComponent<TransformComponent>(400.0f, 0.0f);

    Entity& enemyEntity = manager.addEntity();
    enemyEntity.addComponent<HealthComponent>().currentHealth = 100;
    enemyEntity.addComponent<TransformComponent>(0.0f, 0.0f);

    enemyEntity.addComponent<AIComponent>(playerEntity, enemyEntity.getComponent<TransformComponent>().position, SDL_Rect(), SDL_Rect());

    enemyEntity.getComponent<AIComponent>().setState(0);

    enemyEntity.getComponent<AIComponent>().updateChaseState();

    CHECK_EQUAL(1, enemyEntity.getComponent<AIComponent>().getState());

    playerEntity.getComponent<TransformComponent>().position = Vector2D(50.0f, 0.0f);

    enemyEntity.getComponent<AIComponent>().updateChaseState();

    CHECK_EQUAL(2, enemyEntity.getComponent<AIComponent>().getState());
}

TEST(TestAIComponent_UpdateAttackState) 
{
    Manager manager;
    Entity& playerEntity = manager.addEntity();
    playerEntity.addComponent<HealthComponent>().currentHealth = 100;
    playerEntity.addComponent<TransformComponent>(0.0f, 0.0f);

    Entity& enemyEntity = manager.addEntity();
    enemyEntity.addComponent<HealthComponent>().currentHealth = 100;
    enemyEntity.addComponent<TransformComponent>(0.0f, 0.0f);

    enemyEntity.addComponent<SpriteComponent>().Play("Walk_d");

    enemyEntity.addComponent<AIComponent>(playerEntity, enemyEntity.getComponent<TransformComponent>().position, SDL_Rect(), SDL_Rect());

    enemyEntity.getComponent<AIComponent>().setState(2);

    SDL_Rect p_collider = { 0, 0, 32, 32 };
    SDL_Rect e_collider = { 0, 0, 32, 32 };

    enemyEntity.getComponent<AIComponent>().updateAttackState();

    CHECK_EQUAL(3, enemyEntity.getComponent<AIComponent>().getState());

    enemyEntity.getComponent<AIComponent>().updateFreezeState();

    CHECK_EQUAL(3, enemyEntity.getComponent<AIComponent>().getState());
}

