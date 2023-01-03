#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "Bullet.h"
#include "Obstacle.h"

#include "Entity.h"
#include "Movable.h"
#include "Math.h"

class Player : public Movable
{
public:
    Player(Vector2f p_pos, SDL_Texture* p_tex_l, SDL_Texture* p_tex_r, SDL_Texture* p_powerMTexFG, SDL_Texture* p_powerMTexBG, SDL_Texture* healthMeterTexture_overlay);
    float getHealth()
    {
        return health;
    }
    bool isDead()
    {
        return health == 0;
    }    
    std::vector<Entity> getHealthBar()
    {
        return healthBar;
    }
    void addHealth(float healthVal);
    void setInitialMousePos(float x, float y);
    double getAim();
    bool hitObs(Entity o);
    bool upside();
    void update(double deltaTime, bool keyDown, std::vector<Obstacle> rivers, std::vector<Obstacle> bridges);
private:
    SDL_Texture* tex_l;
    SDL_Texture* tex_r;
    double aim;
    float v_init = 0.3;
    std::vector<Entity> healthBar;
    float health = 100;
    Vector2f initialMousePos;
};