#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "Bullet.h"
#include "Tile.h"

#include "Entity.h"
#include "Math.h"

class Monster : public Entity{
public:
    Monster(Vector2f p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_powerMTexFG, SDL_Texture* p_powerMTexBG);
    Vector2f& getVelocity()
    {
        return velocity;
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
    void setVelocity(float x, float y);
    void setV_factor(float f);
    double getAim();
    void update(double deltaTime, bool keyDown, std::vector<Obstacle> obstacles,Player& player);
private:
    Vector2f velocity = Vector2f(0, 0);
    double aim;
    float v_init = 0.3;
    float v_factor = 1;
    std::vector<Entity> healthBar;
    float health = 100;
    Vector2f initialMousePos;
};
