#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getCurrentFrame().w * p_entity.getScale().x;
	dst.h = p_entity.getCurrentFrame().h * p_entity.getScale().y;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), NULL, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
}

void RenderWindow::render(int p_x, int p_y, SDL_Texture* p_tex)
{
	int x, y;
	SDL_QueryTexture(p_tex, NULL, NULL, &x, &y);

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = x;
	dst.h = y;

	SDL_RenderCopy(renderer, p_tex, NULL, &dst);
}

void RenderWindow::render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	if (surfaceMessage == nullptr)
	{
		SDL_DestroyTexture(message);
		SDL_FreeSurface(surfaceMessage);
		return;
	}

	SDL_Rect dst;
	TTF_SizeText(font, p_text, &dst.w, &dst.h);
	dst.x = p_x;
	dst.y = p_y;

	SDL_RenderCopy(renderer, message, NULL, &dst);
	SDL_DestroyTexture(message);
	SDL_FreeSurface(surfaceMessage);
}

void RenderWindow::renderTextCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor, SDL_Color textColor_sh)
{
	int x, y;
	TTF_SizeText(font, p_text, &x, &y);
	render(p_x - x / 2 + 480, p_y - y / 2 + 360 + 3, p_text, font, textColor_sh);
	render(p_x - x / 2 + 480, p_y - y / 2 + 360, p_text, font, textColor);
}

void RenderWindow::renderOptionCentered(float p_x, float p_y, SDL_Texture* p_tex, const char* p_text, TTF_Font* font, SDL_Color textColor, SDL_Color textColor_sh)
{
	int x, y;
	SDL_QueryTexture(p_tex, NULL, NULL, &x, &y);
	render(p_x - x / 2, p_y - y / 2, p_tex);
	renderTextCenter(p_x - 480, p_y - 360, p_text, font, textColor, textColor_sh);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}