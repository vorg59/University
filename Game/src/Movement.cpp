#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Movement.hpp"
#include "Entity.hpp"
#include "Math.hpp"
using namespace std;

Movement::Movement(int p_speed)
{
	state = true;
	P1_Score = P2_Score = 0; 
	Ball_Velocity_X = 5;
	Ball_Velocity_Y = 5;
	GokuSpeed = p_speed;
	facing = true;
	wPressed = sPressed = iPressed = kPressed = false;
}

void Movement::Input(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) 
	{
	    switch (event.key.keysym.sym) 
	    {
	        case SDLK_UP:
	        case SDLK_i: // 'i' key
	            iPressed = true;
	            break;
	        case SDLK_DOWN:
	        case SDLK_k: // 'k' key
	            kPressed = true;
	            break;
	        case SDLK_LEFT:
	        case SDLK_s: // 's' key
	            sPressed = true;
	            break;
	        case SDLK_RIGHT:
	        case SDLK_w: // 'w' key
	            wPressed = true;
	            break;
	        default:
	            break;
	    }
	} 
	else if (event.type == SDL_KEYUP)
	{
	    switch (event.key.keysym.sym) 
	    {
	        case SDLK_UP:
	        case SDLK_i: // 'i' key
	            iPressed = false;
	            break;
	        case SDLK_DOWN:
	        case SDLK_k: // 'k' key
	            kPressed = false;
	            break;
	        case SDLK_LEFT:
	        case SDLK_s: // 's' key
	            sPressed = false;
	            break;
	        case SDLK_RIGHT:
	        case SDLK_w: // 'w' key
	            wPressed = false;
	            break;
	        default:
	            break;
	    }
	}
}

void Movement::Paddle_Move(Entity& E, bool isLeftPaddle, int Window_Height)
{
    Vector2f pos_f = E.getPos(); // Initialize pos_f with current position

    if (isLeftPaddle) 
    {
        if (wPressed && !sPressed && pos_f.y > 0) 
        {
            pos_f.y -= GokuSpeed;
        } 
        else if (sPressed && !wPressed && pos_f.y < Window_Height - 128) 
        {
            pos_f.y += GokuSpeed;
        }
    } 
    else 
    {
        if (iPressed && !kPressed && pos_f.y > 0) 
        {
            pos_f.y -= GokuSpeed;
        } 
        else if (kPressed && !iPressed && pos_f.y < Window_Height - 128) 
        {
            pos_f.y += GokuSpeed;
        }
    }
    E.setPos(pos_f);
}

void Movement::Ball_Move(Entity& B, Entity& P1, Entity& P2, int Window_Width, int Window_Height)
{
	Vector2f pos_ball = B.getPos();
	// cout<<pos_ball.x<<endl;

	pos_ball.x += Ball_Velocity_X;
	pos_ball.y += Ball_Velocity_Y;

	if(pos_ball.y <= 0 || pos_ball.y >= Window_Height - 32/2)
		Ball_Velocity_Y = - Ball_Velocity_Y;

	if(pos_ball.x <= 0)
	{
		Ball_Velocity_X = 5;
		Ball_Velocity_Y = 5;
		P2_Score++;
		if(P2_Score == 10)
		{
			state = false;
			return;
		}
		pos_ball.x = Window_Width/2;
		pos_ball.y = Window_Height/2;
	}
	if(pos_ball.x >= Window_Width)
	{
		Ball_Velocity_X = 5;
		Ball_Velocity_Y = 5;
		P1_Score++;
		if(P1_Score == 10)
		{
			state = false;
			return;
		}
		pos_ball.x = Window_Width/2;
		pos_ball.y = Window_Height/2;
	}

	if(pos_ball.x <= 32 && pos_ball.y >= P1.getPos().y && pos_ball.y < P1.getPos().y + 128)
	{
		pos_ball.x = 32;
		Ball_Velocity_X-=2;
		Ball_Velocity_Y-=2;
		Ball_Velocity_X = - Ball_Velocity_X;
	}
	if(pos_ball.x >= Window_Width - 32*2 && pos_ball.y >= P2.getPos().y && pos_ball.y < P2.getPos().y + 128)
	{
		pos_ball.x = Window_Width - 64;
		Ball_Velocity_X+=2;
		Ball_Velocity_Y+=2;
		Ball_Velocity_X = - Ball_Velocity_X;
	}

	B.setPos(pos_ball);
}