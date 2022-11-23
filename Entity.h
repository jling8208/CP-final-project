#pragma once

#include "Entity.h"
#include "Position.h"
#include <SDL.h>

enum direction { DEFAULT, UP, DOWN, LEFT, RIGHT };

class Entity
{
public:
	Entity(position p_pos, SDL_Texture* p_tex);
	position& getPos()
	{
		return pos;
	}
	direction getDir()
	{
		return dir;
	}
	position getScale()
	{
		return scale;
	}
	SDL_Texture* getTex();
	void update();
	void setPos(float x, float y);
	void setDir(direction dir);
	SDL_Rect getCurrentFrame();
private:
	position pos;
	direction dir = DEFAULT;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
