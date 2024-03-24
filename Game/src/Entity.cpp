#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Entity.hpp"
#include "Math.hpp"
using namespace std;

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex):pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 0;
	currentFrame.h = 0;
}

void Entity::setPos(Vector2f p_pos)
{
	pos = p_pos;
}

void Entity::setcurrentFrame(float p_x, float  p_y, float  p_w, float  p_h)
{
	currentFrame.x = p_x;
	currentFrame.y = p_y;
	currentFrame.w = p_w;
	currentFrame.h = p_h;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getcurrentFrame()
{
	return currentFrame;
}