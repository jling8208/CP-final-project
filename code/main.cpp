#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <Windows.h>

#include "RenderWindow.h"
#include "Stopwatch.h"
#include "Entity.h"
#include "Movable.h"
#include "Obstacle.h"
#include "Buff.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "Mouse.h"

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	if (TTF_Init() < 0)
		std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Mix_OpenAudio has failed. Error: " << SDL_GetError() << std::endl;
	return true;
}

bool SDLinit = init();

RenderWindow window("Haunted Halloween: escape from the Jack'O'Latern", 960, 760);

SDL_Texture* cursorTexture = window.loadTexture("res/gfx/cursor.png"); 
SDL_Texture* bulletTexture1 = window.loadTexture("res/gfx/bullet1.png");
SDL_Texture* bulletTexture2 = window.loadTexture("res/gfx/bullet2.png");
SDL_Texture* bgTexture = window.loadTexture("res/gfx/bg.png");
SDL_Texture* uiBgTexture = window.loadTexture("res/gfx/UI_bg.png");
SDL_Texture* optionBgTexture = window.loadTexture("res/gfx/option_bg.png");
SDL_Texture* optionSelectBgTexture = window.loadTexture("res/gfx/option_selected_bg.png");
SDL_Texture* optionMiniBgTexture = window.loadTexture("res/gfx/optionMini_bg.png");
SDL_Texture* optionMiniSelectBgTexture = window.loadTexture("res/gfx/optionMini_selected_bg.png");
SDL_Texture* lockTexture = window.loadTexture("res/gfx/lock.png");
SDL_Texture* playerHealthMeterTexture_FG = window.loadTexture("res/gfx/player_healthmeter_fg.png");
SDL_Texture* monsterHealthMeterTexture1_FG = window.loadTexture("res/gfx/monster1_healthmeter_fg.png");
SDL_Texture* monsterHealthMeterTexture2_FG = window.loadTexture("res/gfx/monster2_healthmeter_fg.png");
SDL_Texture* healthMeterTexture_BG = window.loadTexture("res/gfx/healthmeter_bg.png");
SDL_Texture* healthMeterTexture_overlay = window.loadTexture("res/gfx/healthmeter_overlay.png");
SDL_Texture* click2start = window.loadTexture("res/gfx/click2start.png");
SDL_Texture* endscreenOverlayTexture = window.loadTexture("res/gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("res/gfx/splashbg.png");
SDL_Texture* tutorialTexture1 = window.loadTexture("res/gfx/tutorial_1.png");
SDL_Texture* tutorialTexture2 = window.loadTexture("res/gfx/tutorial_2.png");
SDL_Texture* tutorialTexture3 = window.loadTexture("res/gfx/tutorial_3.png");
SDL_Texture* tutorialTexture4 = window.loadTexture("res/gfx/tutorial_4.png");
SDL_Texture* tutorialTexture5 = window.loadTexture("res/gfx/tutorial_5.png");
SDL_Texture* tutorialTexture[5] = { tutorialTexture1, tutorialTexture2, tutorialTexture3, tutorialTexture4, tutorialTexture5 };
SDL_Texture* previousTexture = window.loadTexture("res/gfx/previous.png");
SDL_Texture* nextTexture = window.loadTexture("res/gfx/next.png");
SDL_Texture* playerTextureL = window.loadTexture("res/gfx/player_l.png");
SDL_Texture* playerTextureR = window.loadTexture("res/gfx/player_r.png");
SDL_Texture* monsterTexture1 = window.loadTexture("res/gfx/monster1.png");
SDL_Texture* monsterTexture2 = window.loadTexture("res/gfx/monster2.png");
SDL_Texture* monsterTexture_attack1 = window.loadTexture("res/gfx/monster_attack1.png");
SDL_Texture* monsterTexture_attack2 = window.loadTexture("res/gfx/monster_attack2.png");
SDL_Texture* riverTexture = window.loadTexture("res/gfx/river.png");
SDL_Texture* bridgeTexture = window.loadTexture("res/gfx/bridge.png");
SDL_Texture* medTexture = window.loadTexture("res/gfx/med.png");
SDL_Texture* shieldTexture = window.loadTexture("res/gfx/shield.png");
SDL_Texture* speedTexture = window.loadTexture("res/gfx/speed.png");
SDL_Texture* shieldOnTexture = window.loadTexture("res/gfx/shield_on.png");
SDL_Texture* bulletUpTexture = window.loadTexture("res/gfx/bullet_up.png");
SDL_Texture* buffTexture[3] = { shieldTexture, speedTexture, bulletUpTexture };
SDL_Texture* shieldListedTexture = window.loadTexture("res/gfx/shield_listed.png");
SDL_Texture* speedListedTexture = window.loadTexture("res/gfx/speed_listed.png");
SDL_Texture* bulletUpListedTexture = window.loadTexture("res/gfx/bullet_up_listed.png");
SDL_Texture* buffListedTexture[3] = { shieldListedTexture, speedListedTexture, bulletUpListedTexture };

Mix_Music* titleSfx = Mix_LoadMUS("res/sfx/res_sfx_title.mp3");
Mix_Music* bgmSfx = Mix_LoadMUS("res/sfx/res_sfx_bgm.mp3");
Mix_Music* endSfx = Mix_LoadMUS("res/sfx/res_sfx_end.mp3");
Mix_Chunk* shootSfx = Mix_LoadWAV("res/sfx/res_sfx_shoot.mp3");

SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* fontTitle = TTF_OpenFont("res/font/font.ttf", 64);
TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);

Player player(Vector2f(), playerTextureL, playerTextureR, playerHealthMeterTexture_FG, healthMeterTexture_BG, healthMeterTexture_overlay);
Vector2f monsterPoint[2] = { Vector2f(960 - 48 * 2, 48), Vector2f(48, 720 - 48 * 2) };
std::vector<Monster> monsters = { };
std::vector<Bullet> bullets = { };
std::vector<Obstacle> rivers = { Obstacle(Vector2f(0, 48 * 6), riverTexture) };
std::vector<Obstacle> bridges = { Obstacle(Vector2f(48 * 4, 48 * 6 - 10), bridgeTexture), 
									Obstacle(Vector2f(48 * 9, 48 * 6), bridgeTexture),
									Obstacle(Vector2f(48 * 14, 48 * 6), bridgeTexture) };
Vector2f buffPoint[8] = { Vector2f(48 * 3, 48), Vector2f(48 * 6, 96), 
							Vector2f(48 * 10, 48), Vector2f(48 * 13, 96),
							Vector2f(48 * 6, 720 - 144), Vector2f(48 * 9, 720 - 96),
							Vector2f(48 * 13, 720 - 144), Vector2f(48 * 16, 720 - 96) };
bool buffPointUsed[8] = { false, false, false, false, false, false, false, false };
std::vector<Buff> meds = { };
std::vector<Buff> buffList[3] = { { }, { }, { } }; // 0: shields, 1: speeds, 2: bullets
Stopwatch buffSw[3] = { Stopwatch(), Stopwatch(), Stopwatch() }; // 0: shields, 1: speeds, 2: bullets
bool buffOn[3] = { false, false, false }; // 0: shields, 1: speeds, 2: bullets
int buffWhere[4] = { -1, -1, -1, -1 }; // 0: shields, 1: speeds, 2: bullets, 3: meds
Obstacle shield = Obstacle(Vector2f(), shieldOnTexture);
Mouse mouse = Mouse(Vector2f(0, 0), cursorTexture);

int level = 0;
int level_time = 0;
bool level_start = false;

bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;
bool move = false;

bool titlePlayed = false;
bool secondtitlePlayed = false;
bool end = false;
bool infinite = false;

SDL_Event event;

int state = 0; // 0 = menu, 1 = game, 2 = end screen, 3 = tutorial

double currentTick = 0;
double lastTick = 0;
double deltaTime = 0;

int point = 0;

Stopwatch game_time;
Stopwatch game_control;

void loadLevel(int level)
{
	if (level <= 1)
	{
		player.setPos(36 + 48 * 4, 36 + 48 * 11);
		bullets = {};
		
		point = 0;
		move = false;
		player.addHealth(100);
		game_time.start_timing();
		game_control.start_timing();
	}
	else if (level > 5)
	{
		state = 2;
		return;
	}

	meds = {};
	for (int i = 0; i < 3; i++)
	{
		buffList[i] = {};
	}
	if (level_start)
	{
		monsters = { Monster(monsterPoint[(player.upside() ? 0 : 1)], 30, 0.15, monsterTexture1, monsterTexture_attack1, monsterHealthMeterTexture1_FG, healthMeterTexture_BG, healthMeterTexture_overlay) };
	}
	else
	{
		monsters = {};
	}
	
	level_time = (20 + level * 5) * 1000;
}

std::string getEndingText()
{
	std::string s = "YOU ARE DEAD!";
	if (!player.isDead())
	{
		s = "YOU WIN!";
		infinite = true;
	}
	return s;
}

std::string getGametimeText()
{
	if (state != 2)
	{
		game_time.timing();
	}	
	return "TIME: " + game_time.get_minute_second();
}

std::string getPointText()
{
	std::string s = "POINTS: " + std::to_string(point);
	return s;
}

std::string getLevelText()
{
	if (level > 5)
	{
		return " ";
	}
	else if (level <= 0)
	{
		return "INFINITE MODE";
	}
	std::string s = std::to_string(level);
	s = "LEVEL: " + s;
	return s;
}

bool timer(int delta)
{
	return static_cast<int>(currentTick / delta) != static_cast<int>(lastTick / delta);
}

void loadMonsters()
{
	int p = (int)game_time.get_milisecond() % 2;

	if (level <= 0)
	{
		if (monsters.size() >= (game_time.get_milisecond() + 20000) / 10000)
		{
			return;
		}
		if (game_control.get_milisecond() > std::pow(0.95, -level) * 6000)
		{
			monsters.push_back(Monster(monsterPoint[(p == 0 ? 0 : 1)], 30, 0.15, monsterTexture1, monsterTexture_attack1, monsterHealthMeterTexture1_FG, healthMeterTexture_BG, healthMeterTexture_overlay));
			level--;
			if (level % 5 == 0)
			{
				monsters.push_back(Monster(monsterPoint[(p == 0 ? 1 : 0)], 80, 0.05, monsterTexture2, monsterTexture_attack2, monsterHealthMeterTexture2_FG, healthMeterTexture_BG, healthMeterTexture_overlay));
			}
			game_control.start_timing();
		}
	}
	else
	{
		if (currentTick > 1000 && timer(std::pow(0.8, level - 1) * 6000))
		{
			monsters.push_back(Monster(monsterPoint[(p == 0 ? 0 : 1)], 30, 0.15, monsterTexture1, monsterTexture_attack1, monsterHealthMeterTexture1_FG, healthMeterTexture_BG, healthMeterTexture_overlay));
		}
		if (currentTick > 1000 && timer(std::pow(0.8, level - 1) * 6000 * 5))
		{
			monsters.push_back(Monster(monsterPoint[(p == 0 ? 1 : 0)], 80, 0.05, monsterTexture2, monsterTexture_attack2, monsterHealthMeterTexture2_FG, healthMeterTexture_BG, healthMeterTexture_overlay));
		}
	}
}

int getBuffPointIndex()
{
	int p = (int)currentTick % 4;
	while (buffPointUsed[p + (player.upside() ? 4 : 0)])
	{
		p = (p + 1) % 4;
	}
	p += (player.upside() ? 4 : 0);
	buffPointUsed[p] = true;
	return p;
}

void loadBuff(int i, bool On, void (*activate)(), void (*inactivate)())
{
	for (Buff& b : buffList[i])
	{
		b.update();
	}
	if (buffList[i].size() >= 1 && player.hitObs(buffList[i].at(0)))
	{
		buffList[i].erase(buffList[i].begin(), buffList[i].begin() + 1);
		buffOn[i] = true;
		buffSw[i].start_timing();
		buffPointUsed[buffWhere[i]] = false;
	}
	else if (On && !buffOn[i] && buffList[i].size() < 1)
	{
		int index = getBuffPointIndex();
		buffList[i].push_back(Buff(buffPoint[index], buffTexture[i]));
		buffWhere[i] = index;
	}
	if (buffOn[i])
	{
		activate();
		buffSw[i].timing();
		if (buffSw[i].get_milisecond() > 10000)
		{
			buffOn[i] = false;
		}
	}
	else
	{
		inactivate();
	}
}

void update()
{
	lastTick = currentTick; game_control.timing();
	currentTick = game_control.get_milisecond();
	deltaTime = currentTick - lastTick;	
	
	mousePressed = false;
	//Get controls and events
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
				mousePressed = true;
			}
			break;
		case SDL_KEYDOWN:
			if (level_start)
			{
				move = true;
			}
			switch (event.key.keysym.sym)
			{
			case SDLK_UP: case SDLK_w:
				player.setDir(UP);
				break;
			case SDLK_DOWN: case SDLK_s:
				player.setDir(DOWN);
				break;
			case SDLK_LEFT: case SDLK_a:
				player.setDir(LEFT);
				break;
			case SDLK_RIGHT: case SDLK_d:
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

	if (level > 0 && level_start && currentTick > level_time && monsters.size() == 0)
	{
		level++;
		if (level > 5)
		{
			state = 2;
		}
		level_start = false;
		game_control.start_timing();
		game_control.timing();
	}
	else if (!level_start && game_control.get_milisecond() > 1500)
	{
		level_start = true;
		loadLevel(level);
		game_control.start_timing();
		game_control.timing();
	}

	if (deltaTime <= 0)
	{
		return;
	}

	// update monsters
	if (level_start && (currentTick <= level_time || level <= 0))
	{
		loadMonsters();
	}
	monsters.erase(std::remove_if(monsters.begin(), monsters.end(), [](Monster m) { if (m.isDead()) point += m.point(); return m.isDead(); }), monsters.end());
	std::sort(monsters.begin(), monsters.end(), [](Monster m1, Monster m2) { return m1.getHealthPercent() < m2.getHealthPercent(); });
	for (Monster& m : monsters)
	{
		if (m.attack(player) && !buffOn[0])
		{
			player.addHealth(-0.1);
		}

		for (Bullet& b : bullets)
		{
			if (b.hitObs(m) && !b.isHit())
			{
				m.addHealth(-b.getDamage());
				b.setHit(true);
			}
		}
		m.update(deltaTime, rivers, bridges, player);
	}
	std::sort(monsters.begin(), monsters.end(), [](Monster m1, Monster m2) { return m1.getHealthPercent() > m2.getHealthPercent(); });

	// update player
	if (player.isDead())
	{
		state = 2;
	}
	player.update(deltaTime, move, rivers, bridges);

	// update buffs
	for (Buff& m : meds)
	{
		m.update();
	}
	if (meds.size() >= 1 && player.hitObs(meds.at(0)))
	{
		meds.erase(meds.begin(), meds.begin() + 1);
		player.addHealth(50);
	}
	else if (player.getHealth() < 25 && meds.size() < 1)
	{
		int index = getBuffPointIndex();
		meds.push_back(Buff(buffPoint[index], medTexture)); 
		buffWhere[3] = index;
	}

	loadBuff(0, (monsters.size() > 3 && timer(5000)), []() { shield.setPos(player.getCenter() - Vector2f(shield.getCurrentFrame().w / 2, shield.getCurrentFrame().h / 2)); }, []() {});
	if (level <= 0)
	{
		loadBuff(1, (monsters.size() > 3 && timer(15000)), []() { player.setV_factor(1.5); }, []() { player.setV_factor(1); });
		loadBuff(2, (monsters.size() > 3 && timer(20000)), []() {}, []() {});
	}	
	
	// update bullets
	if (mousePressed)
	{
		if (buffOn[2])
		{
			bullets.push_back(Bullet(player.getCenter(), 6, player.getAim(), bulletTexture2, shootSfx));
		}
		else
		{
			bullets.push_back(Bullet(player.getCenter(), 3, player.getAim(), bulletTexture1, shootSfx));
		}
	}
	for (Bullet& b : bullets)
	{
		b.update(deltaTime);
	}
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet b) { return b.isHit(); }), bullets.end());

	// update cursor
	mouse.update();
}

void graphics()
{
	window.clear();
	window.render(0, 0, bgTexture);	
	window.render(40, 720 + 5, getGametimeText().c_str(), font24, white);
	window.render(240 + 40, 720 + 5, getPointText().c_str(), font24, white);
	window.render(480 + 40, 720 + 5, getLevelText().c_str(), font24, white);

	for (int i = 0, posX = 720 + 40; i < 3; i++)
	{
		if (buffOn[i])
		{
			if ((int)buffSw[i].get_milisecond() < 9200 || (int)buffSw[i].get_milisecond() % 400 >= 200)
			{
				window.render(posX, 720 + 5, buffListedTexture[i]);
			}
			posX += 40;
		}
	}

	for (Obstacle& r : rivers)
	{
		window.render(r);
	}
	for (Obstacle& b : bridges)
	{
		window.render(b);
	}
	for (Buff& m : meds)
	{
		window.render(m);
	}
	for (int i = 0; i < 3; i++)
	{
		for (Buff& b : buffList[i])
		{
			window.render(b);
		}
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
	if (buffOn[0])
	{
		window.render(shield);
	}
	for (Monster& m : monsters)
	{
		window.render(m);
		for (Entity& h : m.getHealthBar())
		{
			window.render(h);
		}
	}
	if (!level_start)
	{
		window.renderTextCenter(0, 0, getLevelText().c_str(), font48, white, black);
	}
	if (state != 2)
	{
		window.render(mouse);
		window.display();
	}	
}

void endscene()
{
	graphics();

	if (!end)
	{
		end = true;
		Mix_HaltMusic();
		Mix_PlayMusic(endSfx, -1);
	}

	int option = 0;
	if (480 - 135 < mouse.getCenter().x && mouse.getCenter().x < 480 + 135
		&& 416 < mouse.getCenter().y && mouse.getCenter().y < 416 + 72)
	{
		option = 1;
	}

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
				if (option == 1)
				{
					Mix_HaltMusic();
					Mix_PlayMusic(titleSfx, -1);
					end = false;
					state = 0;
				}
			}
			break;
		}
	}

	window.render(0, 0, endscreenOverlayTexture);
	window.renderTextCenter(0, -64, getEndingText().c_str(), font48, white, black);
	window.renderTextCenter(0, 0, getPointText().c_str(), font32, white, black);
	window.render(480 - 135, 416, (option == 1 ? optionSelectBgTexture : optionBgTexture));
	window.renderTextCenter(0, -360 + 416 + 36, "BACK TO MENU", font32, white, black);
	mouse.update();
	window.render(mouse);
	window.display();
}

void menu()
{
	game_time.timing();
	currentTick = game_time.get_milisecond();

	if (currentTick < 2000)
	{
		if (!titlePlayed)
		{
			Mix_PlayMusic(titleSfx, -1);
			titlePlayed = true;
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
		window.renderTextCenter(0, 0, "2023.01.04", font32, white, black);
		window.display();
	}
	else
	{
		int option = 0;
		if (480 - 135 < mouse.getCenter().x && mouse.getCenter().x < 480 + 135
			&& 48 * 6 < mouse.getCenter().y && mouse.getCenter().y < 48 * 6 + 72)
		{
			option = 1;
		}
		else if (480 - 135 < mouse.getCenter().x && mouse.getCenter().x < 480 + 135 
			&& 48 * 8 < mouse.getCenter().y && mouse.getCenter().y < 48 * 8 + 72)
		{
			option = 2;
		}
		else if (480 - 135 < mouse.getCenter().x && mouse.getCenter().x < 480 + 135
			&& 48 * 10 < mouse.getCenter().y && mouse.getCenter().y < 48 * 10 + 72)
		{
			option = 3;
		}

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
					if (option == 2 || (option == 3 && infinite))
					{
						Mix_HaltMusic();
						Mix_PlayMusic(bgmSfx, -1);
						state = 1;
						level = 3 - option;
						level_start = false;
						loadLevel(level);
					}
					else if (option == 1)
					{
						state = 3;
					}
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.renderTextCenter(3, -10 - 160 + 4 * SDL_sin(currentTick * (3.14 / 1500)), "Haunted Halloween", fontTitle, white, black);
		window.renderTextCenter(3, 40 - 160 + 4 * SDL_sin(currentTick * (3.14 / 1500)), "escape from the Jack'O'Latern", font32, white, black);
		window.renderOptionCentered(480, 48 * 6 + 36, (option == 1 ? optionSelectBgTexture : optionBgTexture), "TUTORIAL", font32, white, black);
		window.renderOptionCentered(480, 48 * 8 + 36, (option == 2 ? optionSelectBgTexture : optionBgTexture), "ADVENTURE", font32, white, black);
		if (!infinite)
		{
			window.renderOptionCentered(480, 48 * 10 + 36, optionBgTexture, " ", font32, white, black);
			window.render(480 - 24, 48 * 10 + 36 - 24, lockTexture);
		}
		else
		{
			window.renderOptionCentered(480, 48 * 10 + 36, (option == 3 ? optionSelectBgTexture : optionBgTexture), "INFINITE MODE", font32, white, black);
		}
		mouse.update();
		window.render(mouse);
		window.display();
	}
}

void tutorial()
{
	int option = 0;
	static int page = 1;
	if (48 < mouse.getCenter().x && mouse.getCenter().x < 72 + 48
		&& 720 - 72 - 48 < mouse.getCenter().y && mouse.getCenter().y < 720 - 48)
	{
		option = 1;
	}
	else if (144 < mouse.getCenter().x && mouse.getCenter().x < 72 + 144
		&& 720 - 72 - 48 < mouse.getCenter().y && mouse.getCenter().y < 720 - 48)
	{
		option = 2;
	}
	else if (960 - 270 - 48 < mouse.getCenter().x && mouse.getCenter().x < 960 - 48
		&& 720 - 72 - 48 < mouse.getCenter().y && mouse.getCenter().y < 720 - 48)
	{
		option = 3;
	}

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
				switch (option)
				{
				case 1:
					if (page > 1)
					{
						page--;
					}
					break;

				case 2:
					if (page < 5)
					{
						page++;
					}
					break;

				case 3:
					state = 0;
					page = 1;
					return;
				}
			}
			break;
		}
	}
	window.clear();
	window.render(0, 0, bgTexture);

	window.render(0, 0, tutorialTexture[page - 1]);

	if (page > 1)
	{
		window.renderOptionCentered(36 + 48, 720 - 36 - 48, (option == 1 ? optionMiniSelectBgTexture : optionMiniBgTexture), " ", font32, white, black);
		window.render(48, 720 - 72 - 48, previousTexture);
	}
	if (page < 5)
	{
		window.renderOptionCentered(36 + 144, 720 - 36 - 48, (option == 2 ? optionMiniSelectBgTexture : optionMiniBgTexture), " ", font32, white, black);
		window.render(144, 720 - 72 - 48, nextTexture);
	}
	
	window.renderOptionCentered(960 - 135 - 48, 720 - 36 - 48, (option == 3 ? optionSelectBgTexture : optionBgTexture), "BACK TO MENU", font32, white, black);
	mouse.update();
	window.render(mouse);
	window.display();
}

void game()
{
	switch (state)
	{
	case 0:
		menu();
		break;
	case 1:
		update();
		graphics();
		break;
	case 2:
		endscene();
		break;
	case 3:
		tutorial();
		break;
	}
}

int main(int argc, char* args[])
{
	loadLevel(1);
	while (gameRunning)
	{
		game();
	}

	window.cleanUp();
	TTF_CloseFont(font24);
	TTF_CloseFont(font32);
	TTF_CloseFont(font48);
	SDL_Quit();
	TTF_Quit();
	return 0;
}