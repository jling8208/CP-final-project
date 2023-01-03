#include "Bullet.h"
#include "Entity.h"
#include "Movable.h"
#include "Math.h"
#include "Obstacle.h"

#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Bullet::Bullet(Vector2f p_pos, float p_damage, double angle, SDL_Texture* p_tex, Mix_Chunk* shootSfx)
	:Movable(p_pos, p_tex), damage(p_damage)
{
    Mix_PlayChannel(-1, shootSfx, 0);
    setVelocity(velocity1D * cos(angle), velocity1D * sin(angle));
}

void Bullet::setLaunchedVelocity(float x, float y)
{
    launchedVelocity.x = x;
    launchedVelocity.y = y;
}

void Bullet::setHit(bool p_hit)
{
    hit = p_hit;
}

void Bullet::update(double deltaTime)
{
    bool addhit = false;
    if (hit_times >= 2)
    {
        hit = true;
    }

    Vector2f deltaX = Vector2f(getVelocity().x * deltaTime, 0);
    Vector2f deltaY = Vector2f(0, getVelocity().y * deltaTime);

    if ((getPos() + deltaX).x + getCurrentFrame().w > 960)
    {
        setVelocity(-abs(getVelocity().x), getVelocity().y);
        dirX = -1; addhit = true;
    }
    else if ((getPos() + deltaX).x < 0)
    {
        setVelocity(abs(getVelocity().x), getVelocity().y);
        dirX = 1; addhit = true;
    }
    if ((getPos() + deltaY).y + getCurrentFrame().h > 720)
    {
        setVelocity(getVelocity().x, -abs(getVelocity().y));
        dirY = -1; addhit = true;
    }
    else if ((getPos() + deltaY).y < 0)
    {
        setVelocity(getVelocity().x, abs(getVelocity().y));
        dirY = 1; addhit = true;
    }

    if (addhit) { hit_times++; }
    setPos(getPos() + deltaX + deltaY);
}