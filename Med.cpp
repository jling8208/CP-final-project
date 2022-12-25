#include "Med.h"
#include "Entity.h"
#include "Math.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>

Med::Med(Vector2f p_pos, SDL_Texture* p_tex)
:Entity(p_pos, p_tex)
{
}

Med::trigger(Player& player){
    player.addHealth(50);
}
