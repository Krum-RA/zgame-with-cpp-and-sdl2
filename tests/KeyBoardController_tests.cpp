#include "UnitTest++/UnitTest++.h"
#include "Components.h"
#include "Game.hpp"

SUITE(KeyboardControllerTests)
{
    TEST(KeyboardController_Update_MoveUp)
    {
        Manager manager;
        auto& entity(manager.addEntity());
        entity.addComponent<TransformComponent>();
        entity.addComponent<SpriteComponent>();
        entity.addComponent<HealthComponent>();

        KeyboardController controller;
        controller.entity = &entity;
        controller.init();

        Game::event.type = SDL_KEYDOWN;
        Game::event.key.keysym.sym = SDLK_w;

        controller.update();

        TransformComponent& transform = entity.getComponent<TransformComponent>();

        CHECK_EQUAL(-1, transform.velocity.y);
    }

    TEST(KeyboardController_Update_MoveLeft)
    {
        Manager manager;
        auto& entity(manager.addEntity());
        entity.addComponent<TransformComponent>();
        entity.addComponent<SpriteComponent>();
        entity.addComponent<HealthComponent>();

        KeyboardController controller;
        controller.entity = &entity;
        controller.init();

        Game::event.type = SDL_KEYDOWN;
        Game::event.key.keysym.sym = SDLK_a;

        controller.update();

        TransformComponent& transform = entity.getComponent<TransformComponent>();
       

        CHECK_EQUAL(-1, transform.velocity.x);
    }

    TEST(KeyboardController_Update_ShootProjectile)
    {
        Manager manager;
        auto& entity(manager.addEntity());
        entity.addComponent<TransformComponent>();
        entity.addComponent<SpriteComponent>();
        entity.addComponent<HealthComponent>();

        KeyboardController controller;
        controller.entity = &entity;
        controller.init();

        Game::event.type = SDL_KEYDOWN;
        Game::event.key.keysym.sym = SDLK_e;

        controller.update();

        CHECK_EQUAL(1, AssetManager::projectileCounter);
    }

    TEST(KeyboardController_Update_RestoreHealth)
    {
        Manager manager;
        auto& entity(manager.addEntity());
        entity.addComponent<TransformComponent>();
        entity.addComponent<SpriteComponent>();
        entity.addComponent<HealthComponent>();

        KeyboardController controller;
        controller.entity = &entity;
        controller.init();

        Game::event.type = SDL_KEYDOWN;
        Game::event.key.keysym.sym = SDLK_j;

        controller.update();

        HealthComponent& health = entity.getComponent<HealthComponent>();

        CHECK_EQUAL(100, health.currentHealth);
    }
}
