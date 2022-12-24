#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "Bullet.h"
#include "Obstacle.h"

#include "Entity.h"
#include "Math.h"

class Player : public Entity
{
public:
    Player(Vector2f p_pos, SDL_Texture* p_tex_l, SDL_Texture* p_tex_r, SDL_Texture* p_powerMTexFG, SDL_Texture* p_powerMTexBG, SDL_Texture* healthMeterTexture_overlay);
    Vector2f& getVelocity()
    {
        return velocity;
    }
    bool isDead()
    {
        return false;//health == 0;
    }
    std::vector<Entity> getHealthBar()
    {
        return healthBar;
    }
    Vector2f& getCenter();
    void addHealth(float healthVal);
    void setInitialMousePos(float x, float y);
    void setVelocity(float x, float y);
    void setV_factor(float f);
    double getAim();
    bool hitObs(Entity o);
    void update(double deltaTime, bool keyDown, std::vector<Obstacle> obstacles, std::vector<Entity> rivers, std::vector<Entity> bridges);
private:
    SDL_Texture* tex_l;
    SDL_Texture* tex_r;
    Vector2f velocity = Vector2f(0, 0);
    double aim;
    float v_init = 0.3;
    float v_factor = 1;
    std::vector<Entity> healthBar;
    float health = 100;
    Vector2f initialMousePos;
};