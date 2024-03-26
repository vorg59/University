#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Movement.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Utils.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        cout << "HEY .. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;

    if (! (IMG_Init(IMG_INIT_PNG)))
        cout << "IMG_init has failed. Error: " << SDL_GetError() << endl;

    int Window_Width = 800;
    int Window_Height = 600;
    float paddle_Mag = 1;
    int paddle_Speed = paddle_Mag * 14;


    RenderWindow window("PingPong", Window_Width, Window_Height);

    vector<Entity> Numbers;
    {
        utils::Populate(Numbers, window);
    }

    SDL_Texture* Blizzard = window.loadTexture("res/gfx/G.gif");
    Entity background(Vector2f(0, 0), Blizzard);
    background.setcurrentFrame(0, 0, 1080, 1080);

    SDL_Texture* ball = window.loadTexture("res/gfx/Bball.jpg");
    Entity Ball(Vector2f(Window_Width/2, Window_Height/2+50), ball);// x_cord, y_cord
    Ball.setcurrentFrame(0, 0, 32, 32);

    SDL_Texture* paddle = window.loadTexture("res/gfx/BpaddleL.jpg");
    Entity paddleL(Vector2f(0, 0), paddle);// x_cord, y_cord
    paddleL.setcurrentFrame(0, 0, 32, 128);

    paddle = window.loadTexture("res/gfx/BpaddleR.jpg");
    Entity paddleR(Vector2f(Window_Width - 32, 0), paddle);// x_cord, y_cord
    paddleR.setcurrentFrame(0, 0, 32, 128);

    Movement M(paddle_Speed);


    // bool gameRunning = M.getState();
    SDL_Event event;
    const float timeStep = 0.01f;
    float accumalator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    while(M.getState())
    {
        cout<<window.getRefreshRate()<<endl;
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumalator += frameTime;
        while (accumalator >= timeStep)
        {
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                    M.setState();
                    // gameRunning = false;
                M.Input(event);
            }
            accumalator -= timeStep;
        }

        window.clear();
        //window.render(background, 0.5);
        M.Ball_Move(Ball, paddleL, paddleR, Window_Width, Window_Height);
        M.Paddle_Move(paddleL, 1, Window_Height);
        M.Paddle_Move(paddleR, 0, Window_Height);
        window.render(Ball, paddle_Mag);
        window.render(paddleL, paddle_Mag);
        window.render(paddleR, paddle_Mag);
        utils::PrintScores(Numbers, window, M, Window_Width, Window_Height);
        

        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if(frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}