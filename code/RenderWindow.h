#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Entity.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void render(int x, int y, SDL_Texture* p_tex);
	void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	void renderTextCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor, SDL_Color textColor_sh);
	void renderOptionCentered(float p_x, float p_y, SDL_Texture* p_tex, const char* p_text, TTF_Font* font, SDL_Color textColor, SDL_Color textColor_sh);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};