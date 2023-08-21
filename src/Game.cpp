#include "Game.hpp"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "EntityBuilder.h"
#include <sstream>

Map* map;
Manager manager;

Entity& player = manager.addEntity();
Entity& enemy = manager.addEntity();

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 800, 640 };

bool Game::isRunning = false;

AssetManager* Game::assets = new AssetManager(&manager);

Game::Game()
{}


Game::~Game()
{}

void Game::init(const char* title, int xposition, int yposition, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialized" << std::endl;

        window = SDL_CreateWindow(title, xposition, yposition, width, height, flags);
        if (window)
        {
            std::cout << "Window Created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Created" << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    assets->AddTexture("terrain", RESOURCES_PATH "terrain.png");
    assets->AddTexture("player", RESOURCES_PATH "spritesheet_p.png");
    assets->AddTexture("enemy", RESOURCES_PATH "zspritesheet.png");
    assets->AddTexture("projectile", RESOURCES_PATH "proj.png");

    map = new Map("terrain", 3, 32);
    map->LoadMap(RESOURCES_PATH "map.map", 25, 20);

    initCreatures(player, enemy);
}

void Game::initCreatures(Entity& player, Entity& enemy) 
{
    std::vector<Animation> playerAnimations;
    playerAnimations.push_back(Animation("Idle", 0, 2, 300));
    playerAnimations.push_back(Animation("Walk_s", 1, 3, 200));
    playerAnimations.push_back(Animation("Walk_w", 2, 3, 200));
    playerAnimations.push_back(Animation("Walk_d", 3, 3, 200));
    playerAnimations.push_back(Animation("Walk_a", 4, 3, 200));
    playerAnimations.push_back(Animation("Shoot_s", 5, 3, 200));
    playerAnimations.push_back(Animation("Shoot_w", 6, 3, 200));
    playerAnimations.push_back(Animation("Shoot_d", 7, 3, 200));
    playerAnimations.push_back(Animation("Shoot_a", 8, 3, 200));
    playerAnimations.push_back(Animation("Freeze", 9, 3, 200));
    playerAnimations.push_back(Animation("Dead", 10, 1, 200));

    EntityBuilder(player)
        .withTransform(800.0f, 640.0f, 34, 32, 3)
        .withSprite("player", true, playerAnimations)
        .withHealth(100)
        .withKeyboardController()
        .withCollider("player")
        .inGroup(groupPlayers);

    std::vector<Animation> enemyAnimations;
    enemyAnimations.push_back(Animation("Idle", 0, 4, 200));
    enemyAnimations.push_back(Animation("Walk_s", 4, 9, 220));
    enemyAnimations.push_back(Animation("Walk_w", 5, 9, 220));
    enemyAnimations.push_back(Animation("Walk_d", 6, 9, 220));
    enemyAnimations.push_back(Animation("Walk_a", 7, 9, 220));
    enemyAnimations.push_back(Animation("Attack_s", 8, 7, 220));
    enemyAnimations.push_back(Animation("Attack_w", 9, 7, 220));
    enemyAnimations.push_back(Animation("Attack_d", 10, 7, 220));
    enemyAnimations.push_back(Animation("Attack_a", 11, 7, 220));
    enemyAnimations.push_back(Animation("Dead", 16, 1, 220));

    EntityBuilder(enemy)
        .withTransform(250.0f, 250.0f, 33, 32, 3)
        .withSprite("enemy", true, enemyAnimations)
        .withCollider("enemy")
        .withHealth(300)
        .inGroup(groupEnemies)
        .withAI(player, enemy.getComponent<TransformComponent>().position, player.getComponent<ColliderComponent>().collider, enemy.getComponent<ColliderComponent>().collider);

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& enemies(manager.getGroup(Game::groupEnemies));

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}


void Game::update()
{

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;
    SDL_Rect enemyCol = enemy.getComponent<ColliderComponent>().collider;
    Vector2D enemyPos = enemy.getComponent<TransformComponent>().position;


    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol))
        {
            player.getComponent<TransformComponent>().position = playerPos;
        }
        if (Collision::AABB(cCol, enemyCol))
        {
            enemy.getComponent<AIComponent>().setState(1);
        }
    }


    for (auto& p : projectiles)
    {
        if (Collision::AABB(enemy.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
        {
            std::cout << "Hit zombie!" << std::endl;
            enemy.getComponent<HealthComponent>().takeDamage(10);
            p->destroy();
        }
    }

    int mapWidth = 25 * map->GetTileSize();
    int mapHeight = 20 * map->GetTileSize();

    camera.x = player.getComponent<TransformComponent>().position.x - camera.w / 2;
    camera.y = player.getComponent<TransformComponent>().position.y - camera.h / 2;

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;

    int maxX = mapWidth - camera.w;
    int maxY = mapHeight - camera.h;

    if (camera.x > maxX)
        camera.x = maxX;
    if (camera.y > maxY)
        camera.y = maxY;

    
}

void Game::render()
{
    SDL_RenderClear(renderer);

    for (auto& t : tiles)
    {
        t->draw();
    }
    for (auto& c : colliders)
    {
        c->draw();
    }

    for (auto& p : players)
    {
        p->draw();
    }
    for (auto& e : enemies)
    {
        e->draw();
    }
    for (auto& p : projectiles)
    {
        p->draw();
    }

    

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}