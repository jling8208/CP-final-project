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

//這邊的數值都要剪掉物件的高
void Monster::update(double deltaTime, bool keyDown, std::vector<Tile> tiles,Player& player)
{   if (getPos().y>432 && getPos().y<528){
        if(player.getPos().y>=getPos().y){
            setVelocity(0.0,v_factor);
        }
        else {
            setVelocity(0.0,-1*v_factor);
        }
    }
    else if (getPos().y<=432){
            if (player.getPos().y<432){
            setVelocity(v_factor*((player.getPos().x-getPos().x)/std::sqrt(std::pow((player.getPos().x-getPos().x),2)+(player.getPos().y-getPos().y),2)),v_factor*((player.getPos().y-getPos().y)/std::sqrt(std::pow((player.getPos().x-getPos().x),2)+(player.getPos().y-getPos().y),2)));
                }
            else {
                    //bridge1
                if (player.getPos().x<=360){
                    setVelocity(v_factor*(193-getPos().x)/std::sqrt(std::pow((193-getPos().x),2)+(432-getPos().y),2)),v_factor*((432-getPos().y)/std::sqrt(std::pow((193-getPos().x),2)+(432-getPos().y),2)));
                }
                    //bridge2
                else if (player.getPos().x>360 && player.getPos().x<600){
                    setVelocity(v_factor*(433-getPos().x)/std::sqrt(std::pow((433-getPos().x),2)+(432-getPos().y),2)),v_factor*((432-getPos().y)/std::sqrt(std::pow((433-getPos().x),2)+(432-getPos().y),2)));
                }
                    //bridge3
                else {
                    setVelocity(v_factor*(673-getPos().x)/std::sqrt(std::pow((673-getPos().x),2)+(432-getPos().y),2)),v_factor*((432-getPos().y)/std::sqrt(std::pow((673-getPos().x),2)+(432-getPos().y),2)));
                }
        }
    }
    else if (getPos().y>=528){
        if (player.getPos().y>528){
           setVelocity(v_factor*((player.getPos().x-getPos().x)/std::sqrt(std::pow((player.getPos().x-getPos().x),2)+(player.getPos().y-getPos().y),2)),v_factor*((player.getPos().y-getPos().y)/std::sqrt(std::pow((player.getPos().x-getPos().x),2)+(player.getPos().y-getPos().y),2)));
            }

        else {
                    //bridge1
            if (player.getPos().x<=360){
                    setVelocity(v_factor*(193-getPos().x)/std::sqrt(std::pow((193-getPos().x),2)+(528-getPos().y),2)),v_factor*((528-getPos().y)/std::sqrt(std::pow((193-getPos().x),2)+(528-getPos().y),2)));
                }
                    //bridge2
            else if (player.getPos().x>360 && player.getPos().x<600){
                    setVelocity(v_factor*(433-getPos().x)/std::sqrt(std::pow((433-getPos().x),2)+(528-getPos().y),2)),v_factor*((528-getPos().y)/std::sqrt(std::pow((433-getPos().x),2)+(528-getPos().y),2)));
                }
                    //bridge3
            else {
                    setVelocity(v_factor*(673-getPos().x)/std::sqrt(std::pow((673-getPos().x),2)+(528-getPos().y),2)),v_factor*((528-getPos().y)/std::sqrt(std::pow((673-getPos().x),2)+(528-getPos().y),2)));
                }
        }
    }
    }

    setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
}

