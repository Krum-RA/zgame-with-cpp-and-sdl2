#pragma once

#include "Game.hpp"
#include "ECS.h"
#include "Components.h"
#include "AssetManager.h"

class KeyboardController : public Component
{
public:
	
	TransformComponent* transform;
	SpriteComponent* sprite;
	HealthComponent* health;
	Vector2D projectileVelocity;
	int projectileRange = 300;
	int projectileSpeed = 4;
	Vector2D projectilePosition;

	int playerWidth;
	int playerHeight;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		health = &entity->getComponent<HealthComponent>();
		playerWidth = transform->width;
		playerHeight = transform->height;
	}
	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			if (health->currentHealth > 0)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					transform->velocity.y = -1;
					sprite->Play("Walk_w");
					projectileVelocity = Vector2D(0, -1);
					break;
				case SDLK_a:
					transform->velocity.x = -1;
					sprite->Play("Walk_d");
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					projectileVelocity = Vector2D(-1, 0);
					break;
				case SDLK_d:
					transform->velocity.x = 1;
					sprite->Play("Walk_d");
					projectileVelocity = Vector2D(1, 0);
					break;
				case SDLK_s:
					transform->velocity.y = 1;
					sprite->Play("Walk_s");
					projectileVelocity = Vector2D(0, 1);
					break;
				case SDLK_e:
					projectilePosition = Vector2D(transform->position.x + playerWidth, transform->position.y + playerHeight);
					Game::assets->CreateProjectile(projectilePosition, projectileVelocity, projectileRange, projectileSpeed, "projectile");
					if (projectileVelocity == Vector2D(0, -1))
					{
						sprite->Play("Shoot_w");
					}
					else if (projectileVelocity == Vector2D(-1, 0))
					{
						sprite->Play("Shoot_d");
						sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					}
					else if (projectileVelocity == Vector2D(1, 0))
					{
						sprite->Play("Shoot_d");
					}
					else if (projectileVelocity == Vector2D(0, 1))
					{
						sprite->Play("Shoot_s");
					}
					break;
				default:
					break;
				}
			}
			else
			{
				transform->velocity.zero();
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_j:
					health->currentHealth = 100;
					sprite->Play("Idle");
					break;
				default:
					break;
				}
			}
		}
	
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_e:
				sprite->spriteFlip = SDL_FLIP_NONE;
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		}
	}
};