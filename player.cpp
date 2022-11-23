#include "Player.h"
#include "Entity.h"
#include "Math.h"
#include "Tile.h"
#include "Hole.h"

#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Player::Player(Vector2f p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_powerMTexFG, SDL_Texture* p_powerMTexBG)
    :Entity(p_pos, p_tex)
{
    points.push_back(Entity(Vector2f(-64, -64), p_pointTex));
    setScale(4, 4);
    //powerBar.push_back(Entity(Vector2f(-64, -64), p_powerMTexBG));
    //powerBar.push_back(Entity(Vector2f(-64, -64), p_powerMTexFG));
}

void Player::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

void Player::setLaunchedVelocity(float x, float y)
{
    launchedVelocity.x = x;
    launchedVelocity.y = y;
}

void Player::setInitialMousePos(float x, float y)
{
    initialMousePos.x = x;
    initialMousePos.y = y;
}

void Player::setDead(bool p_die)
{
    dead = p_die;
}

void Player::update(double deltaTime, bool keyDown, std::vector<Tile> tiles, std::vector<Hole> holes, Mix_Chunk* chargeSfx, Mix_Chunk* swingSfx, Mix_Chunk* holeSfx)
{
    if (dead)
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

    for (Hole h : holes)
    {
        if (getPos().x + 4 > h.getPos().x && getPos().x + 16 < h.getPos().x + 20 && getPos().y + 4 > h.getPos().y && getPos().y + 16 < h.getPos().y + 20)
        {
            Mix_PlayChannel(-1, holeSfx, 0);
            setDead(true);
            target.x = h.getPos().x;
            target.y = h.getPos().y + 3;
        }
    }

    if (keyDown)
    {
        switch (Entity::getDir())
        {
        case (UP):
            if (getPos().y >= 0)
            {
                setVelocity(0, -init_v);
            }           
            break;

        case (DOWN):
            if (getPos().y + getCurrentFrame().h <= 480)
            {
                setVelocity(0, init_v);
            }          
            break;

        case (LEFT):
            if (getPos().x >= 0)
            {
                setVelocity(-init_v, 0);
            }           
            break;

        case (RIGHT):
            if (getPos().x + getCurrentFrame().w <= 640)
            {
                setVelocity(init_v, 0);
            }
            break;
        }
    }
    else
    {
        setVelocity(0, 0);
    }  

    for (Tile& t : tiles)
    {
        float newX = getPos().x + getVelocity().x;
        float newY = getPos().y;
        if (newX + 10 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 37 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
        {
            setVelocity(0, getVelocity().y);
        }

        newX = getPos().x;
        newY = getPos().y + getVelocity().y;
        if (newX + 10 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 37 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
        {
            setVelocity(getVelocity().x, 0);
        }
    }
    setPos(getPos().x + getVelocity().x, getPos().y + getVelocity().y);
}
