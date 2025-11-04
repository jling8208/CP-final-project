#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.h"

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
	float getAngle()
	{
		return angle;
	}
	Vector2f getScale()
	{
		return scale;
	}
	void setPos(float x, float y);
	void setPos(Vector2f newPos);
	void setDir(direction dir);
	void setScale(float w, float h);
	void setAngle(float angle);
	void setTex(SDL_Texture* newTex);
	SDL_Texture* getTex();
	void update(double deltaTime);
	SDL_Rect getCurrentFrame();
	Vector2f getCenter();
private:
	Vector2f pos;
	direction dir = DEFAULT;
	float angle = 0;
	Vector2f scale = Vector2f(1, 1);
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};