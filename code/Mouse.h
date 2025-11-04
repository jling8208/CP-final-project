#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "Math.h"

#ifndef MOUSE_H
#define MOUSE_H

class Mouse : public Entity
{
public:
	Mouse(Vector2f p_pos, SDL_Texture* p_cursorTex) : Entity(p_pos, p_cursorTex)
	{
		SDL_ShowCursor(false);
	}

	void update()
	{
		int mouseX = 0;
		int mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);
		setPos(mouseX + 2 - getCurrentFrame().w / 2, mouseY + 2 - getCurrentFrame().h / 2);
	}
};

#endif
