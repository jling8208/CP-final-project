#pragma once

#include "Entity.h"
#include "Math.h"
#include <SDL.h>

enum direction { DEFAULT, UP, DOWN, LEFT, RIGHT };

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	Vector2f& getPos()
	{
		return pos;
	}
	direction getDir()
	{
		return dir;
	}
	Vector2f getScale()
	{
		return scale;
	}
	SDL_Texture* getTex();
	void update();
	void setPos(float x, float y);
	void setDir(direction dir);
	SDL_Rect getCurrentFrame();
private:
	Vector2f pos;
	direction dir = DEFAULT;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
