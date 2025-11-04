#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <vector>
#include "Obstacle.h"

#include "Entity.h"
#include "Movable.h"
#include "Math.h"

class Bullet : public Movable
{
public:
    Bullet(Vector2f p_pos, float p_damage, double angle, SDL_Texture* p_tex, Mix_Chunk* shootSfx);
    float getDamage()
    {
        return damage;
    }
    void setDamage(float p_damage)
    {
        damage = p_damage;
    }
    bool isHit()
    {
        return hit;
    }
    void setHit(bool p_hit);
    void setLaunchedVelocity(float x, float y);
    void update(double deltaTime);
private:
    float damage = 0;
    Vector2f target;
    Vector2f launchedVelocity;
    float velocity1D = 0.4;
    Vector2f initialMousePos;
    bool hit = false;
    int hit_times = 0;
};