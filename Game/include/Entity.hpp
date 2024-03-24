#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Math.hpp"
using namespace std;

class Entity
{
private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	Vector2f& getPos()
	{
		return pos;
	}
	void setPos(Vector2f p_pos);
	SDL_Texture* getTex();
	void setcurrentFrame(float p_x, float  p_y, float  p_w, float  p_h);
	SDL_Rect getcurrentFrame();

};