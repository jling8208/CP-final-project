#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "Math.h"

class Movable : public Entity
{
public:
    Movable(Vector2f p_pos, SDL_Texture* p_tex);
    Vector2f& getVelocity()
    {
        return velocity;
    }
    float getV_factor()
    {
        return v_factor;
    }
    void setVelocity(float x, float y);
    void setV_factor(float f);
    bool hitObs(Entity o);

private:
    Vector2f velocity = Vector2f(0, 0);
    float v_factor = 1;
};