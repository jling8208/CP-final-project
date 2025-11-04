#include "Movable.h"
#include "Entity.h"
#include "Math.h"
#include <SDL.h>

Movable::Movable(Vector2f p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{
}

void Movable::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

void Movable::setV_factor(float f)
{
    v_factor = f;
}

bool Movable::hitObs(Entity o)
{
    if (getPos().x + getCurrentFrame().w * getScale().x > o.getPos().x && getPos().x < o.getPos().x + o.getCurrentFrame().w
        && getPos().y + getCurrentFrame().h * getScale().y > o.getPos().y && getPos().y < o.getPos().y + o.getCurrentFrame().h)
    {
        return true;
    }
    else
    {
        return false;
    }
}