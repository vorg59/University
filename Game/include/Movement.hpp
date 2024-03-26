#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Entity.hpp"
#include "Math.hpp"
#include "threads.hpp"
using namespace std;

class Movement
{
private:
	bool state;

	int P1_Score;
	int OLDP1_Score;
	int P2_Score;
	int OLDP2_Score;

	bool wPressed;
	bool sPressed;
	bool iPressed;
	bool kPressed;
	bool facing;
	float GokuSpeed;

	int Ball_Velocity_X;
	int Ball_Velocity_Y;
	void Input(SDL_Event& event);
	void Ball_Move(Entity& B, Entity& P1, Entity& P2, int Window_Width, int Window_Height);
	void Paddle_Move(Entity& E, bool isLeftPaddle, int Window_Height);

public:
	Movement(int p_speed);
	// void Input(SDL_Event& event);

	static void* threadInput(void *tparam);
	// void Paddle_Move(Entity& E, bool isLeftPaddle, int Window_Height);
	// void Ball_Move(Entity& B, Entity& P1, Entity& P2, int Window_Width, int Window_Height);
	static void* threadBall_Move(void *tparam);
	static void* threadPaddle_Move(void *tparam);

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