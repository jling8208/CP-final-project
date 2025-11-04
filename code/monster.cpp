#include "Monster.h"
#include "Player.h"
#include "Entity.h"
#include "Movable.h"
#include "Math.h"

#include <vector>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Monster::Monster(Vector2f p_pos, float p_health_init, float p_velocity,
    SDL_Texture* p_tex_init, SDL_Texture* p_tex_attack,
    SDL_Texture* p_healthMTexFG, SDL_Texture* p_healthMTexBG, SDL_Texture* p_healthMTexFrame)
    :Movable(p_pos, p_tex_init), tex_init(p_tex_init), tex_attack(p_tex_attack), 
        health_init(p_health_init), health(p_health_init), velocity(p_velocity)
{
    healthBar.push_back(Entity(Vector2f(-64, -64), p_healthMTexBG));
    healthBar.push_back(Entity(Vector2f(-64, -64), p_healthMTexFG));
    healthBar.push_back(Entity(Vector2f(-64, -64), p_healthMTexFrame));
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

bool Monster::attack(Player player)
{
    if (hitObs(player))
    {
        setTex(tex_attack);
        return true;
    }
    else
    {
        setTex(tex_init);
        return false;
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

float distance(Vector2f a, Vector2f b)
{
    return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}

void Monster::update(double deltaTime, std::vector<Obstacle> rivers, std::vector<Obstacle> bridges, Player& player)
{
    Obstacle river = rivers.at(0);
    bool onRiver = false;
    bool upside = (getPos().y + getCurrentFrame().h <= river.getPos().y);

    //monster on bridge
    if (getPos().y + getCurrentFrame().h >= river.getPos().y && getPos().y <= river.getPos().y + river.getCurrentFrame().h)
    {
        if (hitObs(player))
        {
            setVelocity(0, velocity * (player.getCenter().y > getCenter().y ? 1 : -1));
        }
        else if (getVelocity().y > 0 || upside)
        {
            setVelocity(0, velocity);
        }
        else
        {
            setVelocity(0, -velocity);
        }
    }
    //monster and player at the same side of the river
    else if ((player.getPos().y + player.getCurrentFrame().h <= river.getPos().y && getPos().y + getCurrentFrame().h <= river.getPos().y)
        || (player.getPos().y >= river.getPos().y + river.getCurrentFrame().h && getPos().y >= river.getPos().y + river.getCurrentFrame().h))
    {
        Vector2f dst =  Vector2f(player.getCenter().x, (upside ? min(player.getCenter().y, river.getPos().y - getCurrentFrame().h / 2) : max(player.getCenter().y, river.getPos().y + river.getCurrentFrame().h + getCurrentFrame().h / 2)));
        Vector2f v = (dst - getCenter()) * (1 / distance(dst, getCenter())) * velocity;
        setVelocity(v.x, v.y);
    }
    //monster and player not at the same side of the river
    else
    {
        float dist = std::sqrt(960 * 960 + 720 * 720);
        Vector2f v = Vector2f();
        for (Obstacle& b : bridges)
        {
            if (distance(player.getCenter(), b.getCenter()) < dist)
            {
                dist = distance(player.getCenter(), b.getCenter());
                v = (Vector2f(b.getCenter().x, river.getCenter().y) - getCenter() + Vector2f(0, (river.getCurrentFrame().h + getCurrentFrame().h) / 2) * (upside ? -1 : 1));
                v = v * (1 / distance(v, Vector2f())) * velocity;
            }
        }
        setVelocity(v.x, v.y); 
    }

    Vector2f currentPos = Vector2f(getPos());
    Vector2f deltaX = Vector2f(getVelocity().x * deltaTime, 0);
    Vector2f deltaY = Vector2f(0, getVelocity().y * deltaTime);
    setPos(currentPos + deltaX + deltaY);

    for (Obstacle& r : rivers)
    {
        if (hitObs(r))
        {
            onRiver = true;
        }

        if (onRiver)
        {
            for (Obstacle& b : bridges)
            {
                if (getPos().x > b.getPos().x && getPos().x + getCurrentFrame().w * getScale().x < b.getPos().x + b.getCurrentFrame().w)
                {
                    onRiver = false; 
                    break;
                }
            }
        }

        if (onRiver)
        {
            setVelocity(getVelocity().x, 0);
        }
    }
    setPos(currentPos.x + getVelocity().x * deltaTime, currentPos.y + getVelocity().y * deltaTime);
    healthBar.at(0).setPos(getCenter().x - 32, getPos().y + getCurrentFrame().h * 1.2);
    healthBar.at(1).setPos(getCenter().x - 29, getPos().y + getCurrentFrame().h * 1.2 + 3);
    healthBar.at(2).setPos(getCenter().x - 32, getPos().y + getCurrentFrame().h * 1.2);
    healthBar.at(1).setScale(health / health_init, 1);
}