#include "Entity.h"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(position p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	//SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

void Entity::update()
{
	
}

void Entity::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
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

void Entity::setCurrentFrame(int x, int y, SDL_Texture* p_tex)
{
	currentFrame.x = x;
	currentFrame.y = y;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
