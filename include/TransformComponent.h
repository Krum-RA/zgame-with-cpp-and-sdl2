#pragma once
#include "Components.h"
#include "Vector2D.h"

struct TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int speed = 3;
	int height = 32;
	int width = 32;
	int scale = 1;
	

	TransformComponent()
	{
		position.zero();
	}

	TransformComponent(int sc)
	{
		position.x = 400;
		position.y = 320;
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		this->position.x = x;
		this->position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.zero();
	}

	float x() { return position.x; }
	float y() { return position.y; }

	
	void update() override
	{
		if (velocity.x != 0 || velocity.y != 0)
		{
			position.x += velocity.x * speed;
			position.y += velocity.y * speed;
		}
	}
};