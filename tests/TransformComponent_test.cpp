#include "UnitTest++/UnitTest++.h"
#include "Components.h"

SUITE(TransformComponentTests)
{
    TEST(ConstructorSetsDefaults)
    {
        Manager manager;
        Entity& entity = manager.addEntity();
        entity.addComponent<TransformComponent>();

        CHECK_EQUAL(0, entity.getComponent<TransformComponent>().x());
        CHECK_EQUAL(0, entity.getComponent<TransformComponent>().y());
        CHECK_EQUAL(0, entity.getComponent<TransformComponent>().velocity.x);
        CHECK_EQUAL(0, entity.getComponent<TransformComponent>().velocity.y);
        CHECK_EQUAL(3, entity.getComponent<TransformComponent>().speed);
        CHECK_EQUAL(32, entity.getComponent<TransformComponent>().height);
        CHECK_EQUAL(32, entity.getComponent<TransformComponent>().width);
        CHECK_EQUAL(1, entity.getComponent<TransformComponent>().scale);
    }

    TEST(ConstructorWithScale)
    {
        Manager manager;
        Entity& entity = manager.addEntity();
        entity.addComponent<TransformComponent>(2);

        CHECK_EQUAL(400, entity.getComponent<TransformComponent>().x());
        CHECK_EQUAL(320, entity.getComponent<TransformComponent>().y());
        CHECK_EQUAL(0, entity.getComponent<TransformComponent>().velocity.x);
        CHECK_EQUAL(0, entity.getComponent<TransformComponent>().velocity.y);
        CHECK_EQUAL(3, entity.getComponent<TransformComponent>().speed);
        CHECK_EQUAL(32, entity.getComponent<TransformComponent>().height);
        CHECK_EQUAL(32, entity.getComponent<TransformComponent>().width);
        CHECK_EQUAL(2, entity.getComponent<TransformComponent>().scale);
    }

    TEST(ConstructorWithPosition)
    {
        Manager manager;
        Entity& entity = manager.addEntity();
        entity.addComponent<TransformComponent>(100, 200);

        CHECK_EQUAL(100, entity.getComponent<TransformComponent>().x());
        CHECK_EQUAL(200, entity.getComponent<TransformComponent>().y());
        CHECK_EQUAL(0, entity.getComponent<TransformComponent>().velocity.x);
        CHECK_EQUAL(0, entity.getComponent<TransformComponent>().velocity.y);
        CHECK_EQUAL(3, entity.getComponent<TransformComponent>().speed);
        CHECK_EQUAL(32, entity.getComponent<TransformComponent>().height);
        CHECK_EQUAL(32, entity.getComponent<TransformComponent>().width);
        CHECK_EQUAL(1, entity.getComponent<TransformComponent>().scale);
    }
    TEST(TransformComponent_Update_NoVelocity_NoChange) 
    {
        TransformComponent transform;
        Vector2D initialPosition = transform.position;

        transform.update();

        CHECK_EQUAL(initialPosition.x, transform.position.x);
        CHECK_EQUAL(initialPosition.y, transform.position.y);
    }

    TEST(TransformComponent_Update_VelocityX_ChangeXPosition) 
    {
        TransformComponent transform;
        Vector2D initialPosition = transform.position;
        transform.velocity.x = 1; 

        transform.update();

        CHECK_EQUAL(initialPosition.x + transform.speed, transform.position.x);
        CHECK_EQUAL(initialPosition.y, transform.position.y);
    }

    TEST(TransformComponent_Update_VelocityY_ChangeYPosition) 
    {
        TransformComponent transform;
        Vector2D initialPosition = transform.position;
        transform.velocity.y = -1; 

        transform.update();

        CHECK_EQUAL(initialPosition.x, transform.position.x);
        CHECK_EQUAL(initialPosition.y - transform.speed, transform.position.y);
    }

    TEST(TransformComponent_Update_VelocityXY_ChangeBothPositions) 
    {
        TransformComponent transform;
        Vector2D initialPosition = transform.position;
        transform.velocity.x = 2;
        transform.velocity.y = -3; 

        transform.update();

        CHECK_EQUAL(initialPosition.x + 2 * transform.speed, transform.position.x);
        CHECK_EQUAL(initialPosition.y - 3 * transform.speed, transform.position.y);
    }

    TEST(TransformComponent_Update_ZeroVelocity_NoChange) 
    {
        TransformComponent transform;
        Vector2D initialPosition = transform.position;
        transform.velocity.x = 0;
        transform.velocity.y = 0;

        transform.update();

        CHECK_EQUAL(initialPosition.x, transform.position.x);
        CHECK_EQUAL(initialPosition.y, transform.position.y);
    }
}
