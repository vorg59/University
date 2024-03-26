#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Entity.hpp"
#include "Math.hpp"
using namespace std;

class Movement
{
private:
	bool state;

	int P1_Score;
	int P2_Score;

	bool wPressed;
	bool sPressed;
	bool iPressed;
	bool kPressed;
	bool facing;
	int GokuSpeed;

	int Ball_Velocity_X;
	int Ball_Velocity_Y;
public:
	Movement(int p_speed);
	void Input(SDL_Event& event);
	void Paddle_Move(Entity& E, bool isLeftPaddle, int Window_Height);
	void Ball_Move(Entity& B, Entity& P1, Entity& P2, int Window_Width, int Window_Height);
	int getP1_Score()
	{
		return P1_Score;
	}
	int getP2_Score()
	{
		return P2_Score;
	}
	void setState()
	{
		state = false;
	}
	bool getState()
	{
		return state;
	}
};