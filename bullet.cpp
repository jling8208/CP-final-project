#include "Bullet.h"
#include "Entity.h"
#include "Math.h"
#include "Obstacle.h"
#include "Hole.h"

#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Bullet::Bullet(Vector2f p_pos, double angle, SDL_Texture* p_tex, Mix_Chunk* shootSfx)
	:Entity(p_pos, p_tex)
{
    Mix_PlayChannel(-1, shootSfx, 0);
    setVelocity(velocity1D * cos(angle), velocity1D * sin(angle));
}

void Bullet::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
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

bool Bullet::hitObs(Obstacle o)
{
    if (getPos().x + getCurrentFrame().w * getScale().x > o.getPos().x && getPos().x < o.getPos().x + o.getCurrentFrame().w
        && getPos().y + getCurrentFrame().h * getScale().y > o.getPos().y && getPos().y < o.getPos().y + o.getCurrentFrame().h)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Bullet::update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Obstacle> obstacles)
{
    bool addhit = false;
    if (hit_times >= 3)
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

    Vector2f currentPos = Vector2f(getPos());
        
    for (Obstacle& o : obstacles)
    {
        setPos(currentPos);
        if (!hitObs(o))
        {
            setPos(currentPos + deltaX);
            if (hitObs(o))
            {
                setVelocity(getVelocity().x * -1, getVelocity().y);
                dirX *= -1; addhit = true;
            }
            setPos(currentPos + deltaY);
            if (hitObs(o))
            {
                setVelocity(getVelocity().x, getVelocity().y * -1);
                dirY *= -1; addhit = true;
            }
            setPos(currentPos + deltaX + deltaY);
            if (!addhit && hitObs(o))
            {
                setVelocity(getVelocity().x * -1, getVelocity().y * -1);
                dirX *= -1; dirY *= -1; addhit = true;
            }
        }
    }
    if (addhit) { hit_times++; }
    setPos(currentPos + deltaX + deltaY);
}