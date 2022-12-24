#include "Player.h"
#include "Entity.h"
#include "Math.h"
#include "Obstacle.h"

#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Player::Player(Vector2f p_pos, SDL_Texture* p_tex_l, SDL_Texture* p_tex_r, SDL_Texture* p_healthMTexFG, SDL_Texture* p_healthMTexBG, SDL_Texture* p_healthMTexFrame)
    :Entity(p_pos, p_tex_r), tex_l (p_tex_l), tex_r(p_tex_r)
{
    setScale(0.5, 0.5);
    healthBar.push_back(Entity(Vector2f(-64, -64), p_healthMTexBG));
    healthBar.push_back(Entity(Vector2f(-64, -64), p_healthMTexFG));
    healthBar.push_back(Entity(Vector2f(-64, -64), p_healthMTexFrame));
    //healthBar.at(0).setScale(0.7, 0.7);
    //healthBar.at(1).setScale(0.7, 0.7);
    //healthBar.at(2).setScale(0.7, 0.7);
}

Vector2f& Player::getCenter()
{
    Vector2f center = Vector2f(getPos().x + getCurrentFrame().w * getScale().x / 2, getPos().y + getCurrentFrame().h * getScale().y / 2);
    return center;
}

void Player::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

void Player::setV_factor(float f)
{
    v_factor = f;
}

void Player::setInitialMousePos(float x, float y)
{
    initialMousePos.x = x;
    initialMousePos.y = y;
}

void Player::addHealth(float healthVal)
{
    health += healthVal;

    if (health <= 0)
    {
        health = 0;
    }
    if (health > 100) 
    { 
        health = 100; 
    }
}

double Player::getAim()
{
    int mouseX = 0;
    int mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    aim = SDL_atan2(mouseY - getCenter().y, mouseX - getCenter().x);
    return aim;
}

bool Player::hitObs(Entity o)
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

void Player::update(double deltaTime, bool move, std::vector<Obstacle> obstacles, std::vector<Entity> rivers, std::vector<Entity> bridges)
{
    healthBar.at(0).setPos(getCenter().x - 32 /*healthBar.at(0).getCurrentFrame().w / 2*/, getPos().y + 55);
    healthBar.at(1).setPos(getCenter().x - 29 /*healthBar.at(1).getCurrentFrame().w / 2*/, getPos().y + 55 + 3);
    healthBar.at(2).setPos(getCenter().x - 32 /*healthBar.at(0).getCurrentFrame().w / 2*/, getPos().y + 55);
    healthBar.at(1).setScale(health / 100, 1); //healthBar.at(1).setScale(health / 100 * 0.7, 0.7);

    if (move)
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
            if (getPos().y + getCurrentFrame().h * getScale().y < 720)
            {
                setVelocity(0, v_init);
            }
            else
            {
                setVelocity(0, 0);
            }
            break;

        case (LEFT):
            tex = tex_l;
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
            tex = tex_r;
            if (getPos().x + getCurrentFrame().w * getScale().x < 960)
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

    Vector2f currentPos = Vector2f(getPos());
    Vector2f deltaX = Vector2f(getVelocity().x * deltaTime, 0);
    Vector2f deltaY = Vector2f(0, getVelocity().y * deltaTime);

    for (Obstacle& o : obstacles)
    {
        setPos(currentPos);
        if (!hitObs(o))
        {
            setPos(currentPos + deltaX);
            if (hitObs(o))
            {
                setVelocity(0, getVelocity().y); addHealth(-0.5);
            }
            
            setPos(currentPos + deltaY);
            if (hitObs(o))
            {
                setVelocity(getVelocity().x, 0); addHealth(-0.5);
            }
        }
    }

    for (Entity& r : rivers)
    {
        bool onRiver = false;
        setPos(currentPos + deltaX);
        if (hitObs(r))
        {
            onRiver = true;
        }

        setPos(currentPos + deltaY);
        if (hitObs(r))
        {
            onRiver = true;
        }

        if (onRiver)
        {
            for (Entity& b : bridges)
            {
                setPos(currentPos + deltaX + deltaY);
                if (getPos().x > b.getPos().x && getPos().x + getCurrentFrame().w * getScale().x < b.getPos().x + b.getCurrentFrame().w)
                {
                    onRiver = false;
                    break;
                }
            }
        }

        if (onRiver)
        {
            setVelocity(0, 0);
        }
    }

    setPos((currentPos + Vector2f(getVelocity().x * deltaTime, getVelocity().y * deltaTime)) * v_factor);
}