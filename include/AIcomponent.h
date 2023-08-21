#pragma once
#include "Components.h"
#include "Collision.h"
#include <thread>
#include <chrono>

class AIComponent : public Component {
private:

    int currentState = 0;
    Entity& playerEntity;

    Vector2D& enemyPos;
    Vector2D previousPosition;

    HealthComponent* health;
    TransformComponent* transform;
    SpriteComponent* sprite;


    SDL_Rect p_collider;
    SDL_Rect e_collider;

    std::vector<Vector2D> patrolWaypoints = { Vector2D(740.0f, 620.0f), Vector2D(300.0f, 400.0f) };
    unsigned int currentWaypointIndex = 0;

    float elapsedTime = 0.0f;
    float idleDuration = 1.0f;



public:
    AIComponent(Entity& player, Vector2D& enemy, SDL_Rect _p_collider, SDL_Rect _e_collider) : playerEntity(player), enemyPos(enemy), p_collider(_p_collider), e_collider(_e_collider) {}

    void init() override
    {
        health = &entity->getComponent<HealthComponent>();
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        previousPosition = transform->position;
    }
    void update() override
    {
        Vector2D movementDirection = transform->position - previousPosition;
        movementDirection.normalize();

        const float threshold = 0.1f;

        if (movementDirection.y < -threshold)
        {
            sprite->Play("Walk_w");
        }
        else if (movementDirection.y > threshold)
        {
            sprite->Play("Walk_s");
        }
        else if (movementDirection.x < -threshold)
        {
            sprite->Play("Walk_a");
        }
        else if (movementDirection.x > threshold)
        {
            sprite->Play("Walk_d");
        }

        previousPosition = transform->position;

        if (health->currentHealth <= 0)
        {
            currentState = 4;
        }
        switch (currentState)
        {
        case 4:
            updateDownedState();
            break;
        case 3:
            updateFreezeState();
            break;
        case 2:
            updateAttackState();
            break;
        case 1:
            updatePatrolState();
            break;
        case 0:
            updateChaseState();
            break;
        default:
            break;
        }
    }
    void setState(int bnum)
    {
        currentState = bnum;
        elapsedTime = 0.0f;
    }

    int getState() { return currentState; }

    void updateDownedState()
    {
        entity->getComponent<TransformComponent>().velocity.zero();

        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_k:
                health->currentHealth = 300;
                setState(0);
                break;
            default:
                break;
            }
        }
    }

    void updateFreezeState()
    {
        elapsedTime += 0.016f;
        Vector2D enemyPosition = enemyPos;
        Vector2D playerPosition = playerEntity.getComponent<TransformComponent>().position;

        Vector2D attackDirection = playerPosition - enemyPosition;
        attackDirection.normalize();

        if (attackDirection.y < -0.5f)
        {
            sprite->Play("Attack_w");
        }
        else if (attackDirection.y > 0.5f)
        {
            sprite->Play("Attack_s");
        }
        else if (attackDirection.x < -0.5f)
        {
            sprite->Play("Attack_a");
        }
        else if (attackDirection.x > 0.5f)
        {
            sprite->Play("Attack_d");
        }

        if (elapsedTime >= idleDuration)
        {
            setState(0);
        }
        if (playerEntity.getComponent<HealthComponent>().currentHealth <= 0)
        {
            setState(1);
        }
    }

    void updatePatrolState()
    {
        Vector2D playerPos = playerEntity.getComponent<TransformComponent>().position;

        Vector2D currentWaypoint = patrolWaypoints[currentWaypointIndex];
        Vector2D direction = currentWaypoint - enemyPos;
        direction.normalize();


        float patrolSpeed = 1.0f;

        Vector2D targetPos = enemyPos + direction * patrolSpeed;

        enemyPos = targetPos;

        float distanceToWaypoint = (currentWaypoint - enemyPos).length();
        if (distanceToWaypoint < 1.0f) 
        {
            
            currentWaypointIndex++;

            
            if (currentWaypointIndex >= patrolWaypoints.size())
            {
                currentWaypointIndex = 0;
            }
        }
        float chaseRange = 200.0f;
        float distanceToPlayer = (playerPos - enemyPos).length();
        if (distanceToPlayer < chaseRange && playerEntity.getComponent<HealthComponent>().currentHealth > 0)
        {
            setState(0);
        }

    }

    void updateChaseState()
    {
        Vector2D playerPos = playerEntity.getComponent<TransformComponent>().position;

        
        Vector2D direction = playerPos - enemyPos;
        direction.normalize();

       
        float chaseSpeed = 2.0f;

        
        Vector2D targetPos = enemyPos + direction * chaseSpeed;

        
        enemyPos = targetPos;

        
        float chaseRange = 300.0f;

        // Check if the player goes out of range
        float distanceToPlayer = (playerPos - enemyPos).length();
        if (distanceToPlayer > chaseRange)
        {
            setState(1);
        }
        if (distanceToPlayer < 50.0f)
        {
            setState(2);
        }
    }
    void updateAttackState()
    {
       
        Vector2D enemyPosition = enemyPos;

       
        Vector2D playerPosition = playerEntity.getComponent<TransformComponent>().position;

        
        Vector2D direction = playerPosition - enemyPosition;
        direction.normalize(); 

        
        float attackSpeed = 4.5f;

        
        Vector2D targetPos = enemyPosition + direction * attackSpeed;

        
        enemyPos = targetPos;

        float attackRange = 50.0f;

        
        float distanceToPlayer = (playerPosition - enemyPosition).length();

        if (Collision::AABB(e_collider, p_collider))
        {
            int damageAmount = 30;
            playerEntity.getComponent<HealthComponent>().takeDamage(damageAmount);
            setState(3);
        }
        else
        {
            setState(0);
        }
    }
};
