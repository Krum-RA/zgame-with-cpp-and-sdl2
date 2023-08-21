#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include "AssetManager.h"
#include <map>
#include <string>

class SpriteComponent : public Component
{
protected:
	
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;
	std::string currentAnimationName;

public:

	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated, const std::vector<Animation>& animList)
	{
		animated = isAnimated;
		animations.clear();

		for (const Animation& anim : animList)
		{
			animations.emplace(anim.name, anim);
		}

		Play("Idle");
		setTex(id);
	}


	~SpriteComponent() {}

	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void init() override
	{

		transform = &entity->getComponent<TransformComponent>();
		

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{

		if (animated)
		{
			if (frames > 0)
			{
				int currentFrame = (SDL_GetTicks() / speed) % frames;
				srcRect.x = srcRect.w * currentFrame;
			}
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x - Game::camera.x);
		destRect.y = static_cast<int>(transform->position.y - Game::camera.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

		
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		currentAnimationName = animName;
		if (animations.find(animName) != animations.end())
		{
			
			frames = animations[animName].frames;
			animIndex = animations[animName].index;
			speed = animations[animName].speed;
		}
	}

	std::string CurrentlyPlaying()
	{
		return currentAnimationName;
	}

};