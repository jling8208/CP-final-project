#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "RenderWindow.h"
#include "Entity.h"
#include "Obstacle.h"
#include "Player.h"
#include "Bullet.h"
#include "Mouse.h"

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	if (TTF_Init() < 0)
		std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Mix_OpenAudio has failed. Error: " << SDL_GetError() << std::endl;
	return true;
}

bool SDLinit = init();

RenderWindow window("myGame", 960, 760);

SDL_Texture* cursorTexture = window.loadTexture("res/gfx/cursor.png"); 
SDL_Texture* bulletTexture = window.loadTexture("res/gfx/bullet.png");
SDL_Texture* obstacleDarkTexture32 = window.loadTexture("res/gfx/tile32_dark.png");
SDL_Texture* obstacleDarkTexture64 = window.loadTexture("res/gfx/tile64_dark.png");
SDL_Texture* obstacleLightTexture32 = window.loadTexture("res/gfx/tile32_light.png");
SDL_Texture* obstacleLightTexture64 = window.loadTexture("res/gfx/tile64_light.png");
SDL_Texture* bgTexture = window.loadTexture("res/gfx/bg.png");
SDL_Texture* uiBgTexture = window.loadTexture("res/gfx/UI_bg.png");
SDL_Texture* levelTextBgTexture = window.loadTexture("res/gfx/levelText_bg.png");
SDL_Texture* healthMeterTexture_FG = window.loadTexture("res/gfx/healthmeter_fg.png");
SDL_Texture* healthMeterTexture_BG = window.loadTexture("res/gfx/healthmeter_bg.png");
SDL_Texture* healthMeterTexture_overlay = window.loadTexture("res/gfx/healthmeter_overlay.png");
SDL_Texture* click2start = window.loadTexture("res/gfx/click2start.png");
SDL_Texture* endscreenOverlayTexture = window.loadTexture("res/gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("res/gfx/splashbg.png");
SDL_Texture* playerTextureL = window.loadTexture("res/gfx/player_l.gif");
SDL_Texture* playerTextureR = window.loadTexture("res/gfx/player_r.gif");
SDL_Texture* riverTexture = window.loadTexture("res/gfx/river.png");
SDL_Texture* bridgeTexture = window.loadTexture("res/gfx/bridge.png");

Mix_Chunk* chargeSfx = Mix_LoadWAV("res/sfx/res_sfx_charge.mp3");
Mix_Chunk* swingSfx = Mix_LoadWAV("res/sfx/res_sfx_swing.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("res/sfx/res_sfx_hole.mp3");
Mix_Chunk* shootSfx = Mix_LoadWAV("res/sfx/res_sfx_swing.mp3");

SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* fontTitle = TTF_OpenFont("res/font/font.ttf", 64);
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);

Player player(Vector2f(0, 0), playerTextureL, playerTextureR, healthMeterTexture_FG, healthMeterTexture_BG, healthMeterTexture_overlay);
std::vector<Bullet> bullets = { };
std::vector<Entity> rivers = { };
std::vector<Entity> bridges = { };
Mouse mouse = Mouse(Vector2f(0, 0), cursorTexture);
//Entity river = Entity(Vector2f(0, 48 * 6), riverTexture);

std::vector<Entity> loadRivers(int level)
{
	std::vector<Entity> temp = {};
	switch (level)
	{
	case 1:
		temp.push_back(Entity(Vector2f(0, 48 * 6), riverTexture));
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		break;
	}
	return temp;
}

std::vector<Entity> loadBridges(int level)
{
	std::vector<Entity> temp = {};
	switch (level)
	{
	case 1:
		temp.push_back(Entity(Vector2f(48 * 4, 48 * 6), bridgeTexture));
		temp.push_back(Entity(Vector2f(48 * 9, 48 * 6), bridgeTexture));
		temp.push_back(Entity(Vector2f(48 * 14, 48 * 6), bridgeTexture));
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		break;
	}
	return temp;
}

std::vector<Obstacle> loadObstacles(int level)
{
	std::vector<Obstacle> temp = {};
	switch (level)
	{
	case 1:
		//temp.push_back(Obstacle(Vector2f(0, 48 * 6), riverTexture));
		break;
	case 2:
		temp.push_back(Obstacle(Vector2f(96 * 2, 96 * 3), obstacleDarkTexture64));

		temp.push_back(Obstacle(Vector2f(96 * 4 + 96 * 5, 96 * 3), obstacleLightTexture64));
		break;
	case 3:
		temp.push_back(Obstacle(Vector2f(48 * 1 + 48 * 10 + 16, 48 * 5), obstacleLightTexture32));
		break;
	case 4:
		temp.push_back(Obstacle(Vector2f(48 * 4, 48 * 7), obstacleDarkTexture64));
		temp.push_back(Obstacle(Vector2f(48 * 3, 48 * 5), obstacleDarkTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 6, 48 * 3), obstacleDarkTexture32));

		temp.push_back(Obstacle(Vector2f(48 * 4 + 96 * 5, 48 * 2), obstacleLightTexture64));
		temp.push_back(Obstacle(Vector2f(48 * 3 + 48 * 10, 48 * 6), obstacleLightTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 6 + 48 * 10, 48 * 9), obstacleLightTexture32));
		break;
	case 5:
		temp.push_back(Obstacle(Vector2f(48 * 3, 48 * 1), obstacleDarkTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 1, 48 * 3), obstacleDarkTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 5, 48 * 3), obstacleDarkTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 3, 48 * 5), obstacleDarkTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 7, 48 * 5), obstacleDarkTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 7, 48 * 10), obstacleDarkTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 3, 48 * 10), obstacleDarkTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 5, 48 * 12), obstacleDarkTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 7, 48 * 10), obstacleDarkTexture32));

		temp.push_back(Obstacle(Vector2f(32*4, 32*7), obstacleDarkTexture64));
		temp.push_back(Obstacle(Vector2f(48 * 8, 48 * 7), obstacleDarkTexture64));

		temp.push_back(Obstacle(Vector2f(48 * 2 + 48 * 10, 48 * 2), obstacleLightTexture32));
		temp.push_back(Obstacle(Vector2f(48 * 5 + 48 * 10, 48 * 11), obstacleLightTexture32));

		temp.push_back(Obstacle(Vector2f(48 * 3 + 48 * 10, 48 * 1), obstacleLightTexture64));
		temp.push_back(Obstacle(Vector2f(48 * 8 + 48 * 10, 48 * 6), obstacleLightTexture64));
		temp.push_back(Obstacle(Vector2f(48 * 3 + 48 * 10, 48 * 11), obstacleLightTexture64));
		break;
	}
	return temp;
}

int level = 1;
std::vector<Obstacle> obstacles = loadObstacles(level);

bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;
bool move = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;


SDL_Event event;

int state = 0; //0 = title screen, 1 = game, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

void loadLevel(int level)
{
	if (level > 5)
	{
		state = 2;
		return;
	}

	obstacles = loadObstacles(level);
	rivers = loadRivers(level);
	bridges = loadBridges(level);

	switch (level)
	{
	case 1:
		player.setPos(36 + 48 * 4, 36 + 48 * 11);
		break;
	case 2:
		player.setPos(36 + 48 * 4, 36 + 48 * 11);
		break;
	case 3:
		player.setPos(36 + 48 * 7, 36 + 48 * 10);
		break;
	case 4:
		player.setPos(36 + 48 * 4, 36 + 48 * 11);
		break;
	case 5:
		player.setPos(36 + 48 * 2, 36 + 48 * 12);
		break;
	}
}

std::string getEndingText()
{
	std::string s = "YOU ARE DEAD!";
	if (!player.isDead())
	{
		s = "YOU WIN!";
	}
	return s;
}

int point = 0;

std::string getPointText()
{
	std::string s = "POINTS: " + std::to_string(point);
	return s;
}

std::string getMapText()
{
	std::string s = "MAP: " + std::to_string(level);
	return s;
}

std::string getLevelText(int side)
{
	int tempLevel = (level + 1) * 2 - 3;
	if (side == 1)
	{
		tempLevel++;
	}
	std::string s = std::to_string(tempLevel);
	s = "AREA: " + s;
	return s;
}

void update()
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

	mousePressed = false;
	//Get our controls and events
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
				if (bullets.size() < 5)
					bullets.push_back(Bullet(player.getCenter(), player.getAim(), bulletTexture, shootSfx));
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				level = 1;
				loadLevel(level);
				break; 
			case SDLK_2:
				level = 2;
				loadLevel(level);
				break;
			case SDLK_3:
				level = 3;
				loadLevel(level);
				break;
			case SDLK_4:
				level = 4;
				loadLevel(level);
				break;
			case SDLK_5:
				level = 5;
				loadLevel(level);
				break;
			case SDLK_ESCAPE:
				level = 6;
				loadLevel(level);
				break;
			case SDLK_SPACE:
				player.addHealth(2);
				break;
			case SDLK_UP: case SDLK_w:
				move = true;
				player.setDir(UP);
				break;
			case SDLK_DOWN: case SDLK_s:
				move = true;
				player.setDir(DOWN);
				break;
			case SDLK_LEFT: case SDLK_a:
				move = true;
				player.setDir(LEFT);
				break;
			case SDLK_RIGHT: case SDLK_d:
				move = true;
				player.setDir(RIGHT);
				break;
			default:
				move = false;
				break;
			}
			break;
		case SDL_KEYUP:
			move = false;
			break;
		}
	}

	if (state == 1)
	{
		switch (level)
		{
		case 1:
			if (player.getPos().y >= 720 - player.getCurrentFrame().h * player.getScale().y && player.getPos().x > 480 - 40 && player.getPos().x + player.getCurrentFrame().w * player.getScale().x < 480 + 40 && move && player.getDir() == DOWN)
			{
				level++; int tempx = player.getPos().x;
				loadLevel(level);
				player.setPos(tempx, 0);
			}
			break;

		case 2:
			if (player.getPos().y <= player.getCurrentFrame().h * player.getScale().y && player.getPos().x > 480 - 40 && player.getPos().x + player.getCurrentFrame().w * player.getScale().x < 480 + 40 && move && player.getDir() == UP)
			{
				level--; int tempx = player.getPos().x;
				loadLevel(level);
				player.setPos(tempx, 720 - player.getCurrentFrame().h * player.getScale().y);
			}
			break;
		}

		if (player.isDead())
		{
			state = 2;
		}
		player.update(deltaTime, move, obstacles, rivers, bridges);
		for (Bullet& b : bullets)
		{
			b.update(deltaTime, mouseDown, mousePressed, obstacles);
		}
		mouse.update();
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [] (Bullet b) { return b.isHit(); }), bullets.end());
	}
}

void graphics()
{
	window.clear();
	window.render(0, 0, bgTexture);
	if (state != 2)
	{
		window.render(40, 720 + 5, getMapText().c_str(), font24, white);
		window.render(240 + 40, 720 + 5, getPointText().c_str(), font24, white);
		window.render(480 + 40, 720 + 5, getLevelText(0).c_str(), font24, white);
		window.render(720 + 40, 720 + 5, getLevelText(1).c_str(), font24, white);
	}
	for (Obstacle& t : obstacles)
	{
		window.render(t);
	}
	for (Entity& r : rivers)
	{
		window.render(r);
	}
	for (Entity& b : bridges)
	{
		window.render(b);
	}
	for (Bullet& b : bullets)
	{
		window.render(b);
	}
	window.render(player);
	for (Entity& h : player.getHealthBar())
	{
		window.render(h);
	}
	window.render(mouse);
	if (state == 2)
	{
		window.render(0, 0, endscreenOverlayTexture);
		window.renderCenter(0, 3 - 32, getEndingText().c_str(), font48, black);
		window.renderCenter(0, -32, getEndingText().c_str(), font48, white);
		window.renderCenter(0, 3 + 32, getPointText().c_str(), font32, black);
		window.renderCenter(0, 32, getPointText().c_str(), font32, white);
	}
	window.display();
}

void titleScreen()
{
	if (SDL_GetTicks() < 2000)
	{
		if (!swingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			swingPlayed = true;
		}
		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			}
		}

		window.clear();
		window.render(0, 0, bgTexture);
		window.render(0, 0, splashBgTexture);
		window.renderCenter(0, 0 + 3, "myGame test", font32, black);
		window.renderCenter(0, 0, "myGame test", font32, white);
		window.display();
	}
	else
	{
		if (!secondSwingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			secondSwingPlayed = true;
		}
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Mix_PlayChannel(-1, holeSfx, 0);
					state = 1;
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.renderCenter(3, - 10 + 3 - 50 + 4 * SDL_sin(SDL_GetTicks() * (3.14 / 1500)), "Some Title", fontTitle, black);
		window.renderCenter(0, - 10 - 50 + 4 * SDL_sin(SDL_GetTicks() * (3.14 / 1500)), "Some Title", fontTitle, white);
		window.renderCenter(3, 40 + 3 - 50 + 4 * SDL_sin(SDL_GetTicks() * (3.14 / 1500)), "Some Subtitle", font32, black);
		window.renderCenter(0, 40 - 50 + 4 * SDL_sin(SDL_GetTicks() * (3.14 / 1500)), "Some Subtitle", font32, white);
		window.render(160, 80, click2start);
		window.renderCenter(0, 200 - 48 + 3 - 16 * 5, "LEFT CLICK TO START", font32, black);
		window.renderCenter(0, 200 - 48 - 16 * 5, "LEFT CLICK TO START", font32, white);
		mouse.update();
		window.render(mouse);
		window.display();
	}
}

void game()
{
	if (state == 0)
	{
		titleScreen();
	}
	else
	{
		update();
		graphics();
	}
}

int main(int argc, char* args[])
{ 
	loadLevel(level);
	while (gameRunning)
	{
		game();
	}

	window.cleanUp();
	TTF_CloseFont(font32);
	TTF_CloseFont(font24);
	SDL_Quit();
	TTF_Quit();
	return 0;
}