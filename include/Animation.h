#pragma once
#include <string>

struct Animation
{

	const char* name;
	int index;
	int frames;
	int speed;

	Animation() {}
	Animation(const char* n, int i, int f, int s)
	{
		name = n;
		index = i;
		frames = f;
		speed = s;
	}
};