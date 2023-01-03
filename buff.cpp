#include "Entity.h"
#include "Buff.h"
#include "Math.h"
#include <SDL.h>

Buff::Buff(Vector2f p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex), init_pos(p_pos)
{
}

void Buff::update()
{
	setPos(init_pos + Vector2f(0, 5 * SDL_sin(SDL_GetTicks() * (3.14 / 1500))));
}