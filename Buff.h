#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "Math.h"

class Buff : public Entity
{
public:
    Buff(Vector2f p_pos, SDL_Texture* p_tex);
    void update();

private:
    Vector2f init_pos = Vector2f();
};