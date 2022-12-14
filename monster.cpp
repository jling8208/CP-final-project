#include "Monster.h"
#include "Player.h"
#include "Entity.h"
#include "Math.h"
#include "Tile.h"
#include "Bullet.h"

#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Monster::Monster(Vector2f p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_healthMTexFG, SDL_Texture* p_healthMTexBG)
    :Entity(p_pos, p_tex)
{
    setScale(1.5, 1.5);
    healthBar.push_back(Entity(Vector2f(-64, -64), p_healthMTexBG));
    healthBar.push_back(Entity(Vector2f(-64, -64), p_healthMTexFG));
}

void Monster::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

void Monster::setV_factor(float f)
{
    v_factor = f;
}

void Monster::setInitialMousePos(float x, float y)
{
    initialMousePos.x = x;
    initialMousePos.y = y;
}

void Monster::addHealth(float healthVal)
{
    health += healthVal;

    if (health < 0)
    {
        health = 0;
    }
    if (health > 100) 
    { 
        health = 100; 
    }
}

double Monster::getAim()
{
    int mouseX = 0;
    int mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    aim = SDL_atan2(mouseY - getPos().y, mouseX - getPos().x) * (180 / 3.1415) + 90;
    return aim;
}

void Monster::update(double deltaTime, bool keyDown, std::vector<Tile> tiles)
{
    healthBar.at(0).setPos(getPos().x + 32 + 8, getPos().y + 32);
    healthBar.at(1).setPos(getPos().x + 32 + 8 + 4, getPos().y + 32 + 4);
    healthBar.at(1).setScale(health / 100, 1);

    if (keyDown)
    {
        switch (Entity::getDir())
        {
        case (UP):
            if (getPos().y > 0)
            {
                setVelocity(0, -v_init);
            }
            else
            {
                setVelocity(0, 0);
            }
            break;

        case (DOWN):
            if (getPos().y + getCurrentFrame().h * getScale().y < 480)
            {
                setVelocity(0, v_init);
            }
            else
            {
                setVelocity(0, 0);
            }
            break;

        case (LEFT):
            if (getPos().x > 0)
            {
                setVelocity(-v_init, 0);
            }
            else
            {
                setVelocity(0, 0);
            }
            break;

        case (RIGHT):
            if (getPos().x + getCurrentFrame().w * getScale().x < 640)
            {
                setVelocity(v_init, 0);
            }
            else
            {
                setVelocity(0, 0);
            }
            break;
        }
    }
    else
    {
        setVelocity(0, 0);
    }

    for (Obstacle& o : obstacles)
    {
        float newX = getPos().x + getVelocity().x * deltaTime;
        float newY = getPos().y;
        if (newX + getCurrentFrame().w * getScale().x > o.getPos().x && newX < o.getPos().x + o.getCurrentFrame().w && newY + getCurrentFrame().h * getScale().y > o.getPos().y && newY < o.getPos().y + o.getCurrentFrame().h - 3)
        {
            setVelocity(0, getVelocity().y);
        }

        newX = getPos().x;
        newY = getPos().y + getVelocity().y * deltaTime;
        if (newX + getCurrentFrame().w * getScale().x > o.getPos().x && newX < o.getPos().x + o.getCurrentFrame().w && newY + getCurrentFrame().h * getScale().y > o.getPos().y && newY < o.getPos().y + o.getCurrentFrame().h - 3)
        {
            setVelocity(getVelocity().x, 0);
        }
    }
    setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
}

