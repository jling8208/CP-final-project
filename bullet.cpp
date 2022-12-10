#include "Bullet.h"
#include "Entity.h"
#include "Math.h"
#include "Obstacle.h"
#include "Hole.h"

#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Bullet::Bullet(Vector2f p_pos, double angle, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{
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

bool intilex(int x, Obstacle o, int h, int w)
{
    if (x + w > o.getPos().x && x < o.getPos().x + o.getCurrentFrame().w)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool intiley(int y, Obstacle o, int h, int w)
{
    if (y + h > o.getPos().y && y < o.getPos().y + o.getCurrentFrame().h)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool intile(Vector2f pos, Obstacle o, int h, int w)
{
    if (intilex(pos.x, o, h, w) && intiley(pos.y, o, h, w))
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
        setHit(true);
    }
    if (hit)
    {
        if (getPos().x < target.x)
        {
            setPos(getPos().x += 0.1 * deltaTime, getPos().y);
        }
        else if (getPos().x > target.x)
        {
            setPos(getPos().x -= 0.1 * deltaTime, getPos().y);
        }
        if (getPos().y < target.y)
        {
            setPos(getPos().x, getPos().y += 0.1 * deltaTime);
        }
        else if (getPos().y > target.y)
        {
            setPos(getPos().x, getPos().y -= 0.1 * deltaTime);
        }
        setScale(getScale().x - 0.001 * deltaTime, getScale().y - 0.001 * deltaTime);
        return;
    }
    
    setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
    
    

    for (Obstacle& o : obstacles)
    {
        //Vector2f newPosXY = Vector2f(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
        float v_x, v_y;
        Vector2f newPosX = Vector2f(getPos().x + getVelocity().x * deltaTime, getPos().y);
        Vector2f newPosY = Vector2f(getPos().x, getPos().y + getVelocity().y * deltaTime);
        
        if (newPosX.x + getCurrentFrame().w > 640)
        {
            setVelocity(-abs(getVelocity().x), getVelocity().y);
            dirX = -1; addhit = true;
        }
        else if (newPosX.x < 0)
        {
            setVelocity(abs(getVelocity().x), getVelocity().y);
            dirX = 1; addhit = true;
        }
        else if (newPosY.y + getCurrentFrame().h > 480)
        {
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            dirY = -1; addhit = true;
        }
        else if (newPosY.y < 0)
        {
            setVelocity(getVelocity().x, abs(getVelocity().y));
            dirY = 1; hit_times++;
        }
        
        if (intile(Vector2f(getPos().x + getVelocity().x * deltaTime, getPos().y), o, getCurrentFrame().h, getCurrentFrame().w) && !intile(Vector2f(getPos().x/**/ - getVelocity().x * deltaTime, getPos().y), o, getCurrentFrame().h, getCurrentFrame().w))
        {
            setVelocity(getVelocity().x * -1, getVelocity().y);
            dirX *= -1; addhit = true;
        }
        if (intile(Vector2f(getPos().x, getPos().y + getVelocity().y * deltaTime), o, getCurrentFrame().h, getCurrentFrame().w) && !intile(Vector2f(getPos().x, getPos().y - getVelocity().y * deltaTime), o, getCurrentFrame().h, getCurrentFrame().w))
        {
            setVelocity(getVelocity().x, getVelocity().y * -1);
            dirY *= -1; addhit = true; 
        }
        if (intile(Vector2f(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime), o, getCurrentFrame().h, getCurrentFrame().w) && !intile(Vector2f(getPos().x - getVelocity().x * deltaTime, getPos().y - getVelocity().y * deltaTime), o, getCurrentFrame().h, getCurrentFrame().w))
        {
            setVelocity(getVelocity().x * -1, getVelocity().y * -1);
            dirX *= -1; dirY *= -1; addhit = true;
        }
    }
    if (addhit) { hit_times++; }
    setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
}
