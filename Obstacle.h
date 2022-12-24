#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "Math.h"

class Obstacle : public Entity
{
public:
    Obstacle(Vector2f p_pos, SDL_Texture* p_tex);

private:
};