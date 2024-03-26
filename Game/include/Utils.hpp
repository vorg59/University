#pragma once
#include "SDL2/SDL.h"
#include "Entity.hpp"
#include "Movement.hpp"
#include <vector>
#include "RenderWindow.hpp"
#include "SDL2/SDL_image.h"

namespace utils
{
	inline float hireTimeInSeconds()
	{
		float t = SDL_GetTicks();
		t *= 0.001f;
		return t;
	}
	inline void Populate(vector<Entity>& Numbers,RenderWindow& window)
	{
		SDL_Texture* nums = window.loadTexture("res/gfx/0.png");
        Entity num0(Vector2f(0, 0), nums);
        num0.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num0); 
        nums = window.loadTexture("res/gfx/1.png");
        Entity num1(Vector2f(0, 0), nums);
        num1.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num1);
        nums = window.loadTexture("res/gfx/2.png");
        Entity num2(Vector2f(0, 0), nums);
        num2.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num2);
        nums = window.loadTexture("res/gfx/3.png");
        Entity num3(Vector2f(0, 0), nums);
        num3.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num3);
        nums = window.loadTexture("res/gfx/4.png");
        Entity num4(Vector2f(0, 0), nums);
        num4.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num4);
        nums = window.loadTexture("res/gfx/5.png");
        Entity num5(Vector2f(0, 0), nums);
        num5.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num5);
        nums = window.loadTexture("res/gfx/6.png");
        Entity num6(Vector2f(0, 0), nums);
        num6.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num6);
        nums = window.loadTexture("res/gfx/7.png");
        Entity num7(Vector2f(0, 0), nums);
        num7.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num7);
        nums = window.loadTexture("res/gfx/8.png");
        Entity num8(Vector2f(0, 0), nums);
        num8.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num8);
        nums = window.loadTexture("res/gfx/9.png");
        Entity num9(Vector2f(0, 0), nums);
        num9.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num9);
        nums = window.loadTexture("res/gfx/10.png");
        Entity num10(Vector2f(0, 0), nums);
        num10.setcurrentFrame(0, 0, 190, 320);
        Numbers.push_back(num10);
	}
	inline Entity getScore(vector<Entity>& E, int s)
	{
		return E[s];
	}	
	inline void PrintScores(vector<Entity>& Numbers,RenderWindow& window, Movement& M, int Window_Width, int Window_Height)
	{
        for (int i = 0; i < 2; ++i)
        {
            if(i==0)
            {
                Entity e = utils::getScore(Numbers, M.getP1_Score());
                e.setPos(Vector2f(Window_Width*0.078125,Window_Height*0.013889));
                window.render(e, 0.2);

            }
            else
            {
                Entity e = utils::getScore(Numbers, M.getP2_Score());
                e.setPos(Vector2f(Window_Width*0.078125+40,Window_Height*0.013889));
                window.render(e, 0.2);

            }
        }
	}
}