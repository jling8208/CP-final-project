#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Med.h"
#include "Entity.h"
#include "Math.h"
#include "Player.h"

class Med : public Entity
{
public:
    Med(Vector2f p_pos, SDL_Texture* p_tex);
    trigger (Player& player);
private:
};
