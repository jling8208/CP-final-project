#include "Entity.h"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

void Entity::update(double deltaTime)
{
	
}

void Entity::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Entity::setPos(Vector2f newPos)
{
	pos = newPos;
}

void Entity::setDir(direction p_dir)
{
	dir = p_dir;
}

void Entity::setScale(float w, float h)
{
	scale.x = w;
	scale.y = h;
}

void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}

void Entity::setTex(SDL_Texture* newTex)
{
	tex = newTex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

Vector2f Entity::getCenter()
{
	Vector2f center = Vector2f(getPos().x + getCurrentFrame().w * getScale().x / 2, getPos().y + getCurrentFrame().h * getScale().y / 2);
	return center;
}