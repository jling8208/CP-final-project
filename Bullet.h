#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <vector>
#include "Hole.h"
#include "Obstacle.h"

#include "Entity.h"
#include "Math.h"

class Bullet : public Entity
{
public:
    Bullet(Vector2f p_pos, double angle, SDL_Texture* p_tex, Mix_Chunk* shootSfx);
    Vector2f& getVelocity()
    {
        return velocity;
    }
    bool isHit()
    {
        return hit;
    }
    void setHit(bool p_hit);
    void setVelocity(float x, float y);
    void setLaunchedVelocity(float x, float y);
    bool hitObs(Obstacle o);
    void update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Obstacle> obstacles);
private:
    Vector2f velocity;
    Vector2f target;
    Vector2f launchedVelocity;
    float velocity1D = 0.6;
    Vector2f initialMousePos;
    int dirX = 1;
    int dirY = 1;
    bool hit = false;
    int hit_times = 0;
};