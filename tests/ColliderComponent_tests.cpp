#include "UnitTest++/UnitTest++.h"
#include "Components.h"

SUITE(ColliderComponentTests)
{
    TEST(ColliderComponent_Init_DefaultConstructor)
    {
        Manager manager;
        auto& entity(manager.addEntity());
        ColliderComponent collider("player");
        entity.addComponent<ColliderComponent>("player");

        collider.entity = &entity;
        collider.init();

        CHECK_EQUAL("player", collider.tag);
    }

    TEST(ColliderComponent_Init_PositionSizeConstructor)
    {
        Manager manager;
        auto& entity(manager.addEntity());
        ColliderComponent collider("obstacle", 100, 100, 32);
        entity.addComponent<ColliderComponent>("obstacle");
        entity.addComponent<TransformComponent>();

        collider.entity = &entity;
        collider.init();

        TransformComponent& transform = entity.getComponent<TransformComponent>();

        CHECK_EQUAL("obstacle", collider.tag);
        CHECK_EQUAL(&transform, collider.transform);
    }
    TEST(ColliderComponent_Update)
    {
        Manager manager;
        auto& entity(manager.addEntity());
        entity.addComponent<TransformComponent>();

        ColliderComponent collider("obstacle");
        collider.entity = &entity;

        collider.init();

        Game::camera.x = 50;
        Game::camera.y = 50;

        TransformComponent& transform = entity.getComponent<TransformComponent>();
        transform.position.x = 150;
        transform.position.y = 150;
        transform.width = 32;
        transform.height = 32;
        transform.scale = 1.0;

        collider.update();

        CHECK_EQUAL(150, collider.collider.x);
        CHECK_EQUAL(150, collider.collider.y);
        CHECK_EQUAL(32, collider.collider.w);
        CHECK_EQUAL(32, collider.collider.h);

        CHECK_EQUAL(100, collider.destR.x);
        CHECK_EQUAL(100, collider.destR.y);
    }
    
}
