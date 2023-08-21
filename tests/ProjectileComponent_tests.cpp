#include "UnitTest++/UnitTest++.h"
#include "Components.h"

SUITE(ProjectileComponentTests)
{
    TEST(ProjectileComponent_Initialization)
    {
        Manager manager;
        Vector2D velocity(1.0f, -1.0f);
        
        auto& projectile(manager.addEntity());
        projectile.addComponent<TransformComponent>(0.0f, 0.0f, 16, 16, 1);
        projectile.addComponent<ProjectileComponent>(100, 10, velocity);
       
        ProjectileComponent& projectileC = projectile.getComponent<ProjectileComponent>();

        CHECK_EQUAL(100, projectileC.getrange());
        CHECK_EQUAL(10, projectileC.getspeed());
        CHECK_EQUAL(0, projectileC.getdistance());
    }

    TEST(ProjectileComponent_Update_InRange)
    {
        Manager manager;
        Vector2D pos(50.0f, 50.0f);
        Vector2D velocity(1.0f, 0.0f);
        
        auto& projectile(manager.addEntity());
        projectile.addComponent<TransformComponent>(0.0f, 0.0f, 16, 16, 1);
        projectile.addComponent<ProjectileComponent>(100, 10, velocity);
        
        TransformComponent& transform = projectile.getComponent<TransformComponent>();
        transform.position = pos;

        ProjectileComponent& projectilec = projectile.getComponent<ProjectileComponent>();
        projectilec.update();

        CHECK_EQUAL(10, projectilec.getdistance());
    }

    TEST(ProjectileComponent_Update_OutOfRange)
    {
        Manager manager;
        Vector2D pos(50.0f, 50.0f);
        Vector2D velocity(1.0f, 0.0f);

        auto& projectile(manager.addEntity());
        projectile.addComponent<TransformComponent>(0.0f, 0.0f, 16, 16, 1);
        projectile.addComponent<ProjectileComponent>(100, 10, velocity);

        TransformComponent& transform = projectile.getComponent<TransformComponent>();
        transform.position = pos;

        ProjectileComponent& projectilec = projectile.getComponent<ProjectileComponent>();

        for (int i = 0; i < 11; ++i)
        {
            projectilec.update();
        }
        bool dead = !projectile.isActive();

        CHECK_EQUAL(true, dead);
    }

    TEST(ProjectileComponent_Update_OutOfBounds)
    {
        Manager manager;
        Vector2D pos(50.0f, 50.0f);
        Vector2D velocity(-1.0f, 0.0f);

        auto& projectile(manager.addEntity());
        projectile.addComponent<TransformComponent>(0.0f, 0.0f, 16, 16, 1);
        projectile.addComponent<ProjectileComponent>(100, 10, velocity);
        
        TransformComponent& transform = projectile.getComponent<TransformComponent>();
        transform.position = pos;

        ProjectileComponent& projectilec = projectile.getComponent<ProjectileComponent>();

        for (int i = 0; i < 51; ++i)
        {
            projectilec.update();
        }
        bool dead = !projectile.isActive();

        CHECK_EQUAL(true, dead);
    }
}
