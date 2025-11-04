#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>

#include "Player.h"
#include "Entity.h"
#include "Movable.h"
#include "Math.h"

class Monster : public Movable {
public:
    Monster(Vector2f p_pos, float p_health_init, float p_velocity, 
        SDL_Texture* p_tex_init, SDL_Texture* p_tex_attack, 
        SDL_Texture* p_healthMTexFG, SDL_Texture* p_healthMTexBG, SDL_Texture* p_healthMTexFrame);
    bool isDead()
    {
        return health == 0;
    }
    int point()
    {
        return (int)(health_init / 2);
    }
    float getHealthPercent()
    {
        return (float)(health * 100 / health_init);
    }
    std::vector<Entity> getHealthBar()
    {
        return healthBar;
    }
    void addHealth(float healthVal);
    bool attack(Player player);
    double getAim();
    void update(double deltaTime, std::vector<Obstacle> rivers, std::vector<Obstacle> bridges, Player& player);
private:
    double aim;
    float velocity;
    std::vector<Entity> healthBar;
    float health_init; 
    float health;
    Vector2f initialMousePos;
    SDL_Texture* tex_init;
    SDL_Texture* tex_attack;
};