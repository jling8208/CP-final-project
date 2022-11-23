#include "Entity.h"
#include "Position.h"
#include <SDL.h>

enum direction { DEFAULT, UP, DOWN, LEFT, RIGHT };

class Entity
{
public:
	Entity(position p_pos, SDL_Texture* p_tex);
	position& getPos()
	{
		return pos;
	}
	direction getDir()
	{
		return dir;
	}
	float getAngle()
	{
		return angle;
	}
	Vector2f getScale()
	{
		return scale;
	}
	void setPos(float x, float y);
	void setDir(direction dir);
	SDL_Texture* getTex();
	void update();
	void setCurrentFrame(int x, int y, int w, int h, SDL_Texture* p_tex);
	SDL_Rect getCurrentFrame();
private:
	position pos;
	direction dir = DEFAULT;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
