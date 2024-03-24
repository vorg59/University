#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

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
    
    RenderWindow window("PingPong", 800, 450);
    vector<Entity> entites2;
    
        SDL_Texture* Blizzard = window.loadTexture("res/gfx/blizzard.png");
        Entity background(Vector2f(0, 0), Blizzard);
        background.setcurrentFrame(0, 0, 800, 450);
        entites2.push_back(background);

        SDL_Texture* Goku = window.loadTexture("res/gfx/gokuR.png");
        int GokuX = 100;
        int GokuY = 200;
        Entity character0(Vector2f(GokuX, GokuY), Goku);// x_cord, y_cord
        character0.setcurrentFrame(0, 0, 212, 100);// width, height
        entites2.push_back(character0);

        SDL_Texture* GokuL = window.loadTexture("res/gfx/gokuL.png");
        Entity character0_L(Vector2f(GokuX, GokuY), GokuL);// x_cord, y_cord
        character0_L.setcurrentFrame(0, 0, 212, 100);// width, height
        entites2.push_back(character0_L);

        SDL_Texture* Vegeta = window.loadTexture("res/gfx/vegetaL.png");
        Entity character1(Vector2f(600, 100), Vegeta);
        character1.setcurrentFrame(0, 0, 169, 176);
        entites2.push_back(character1);
       
        // SDL_Texture* Gogeta = window.loadTexture("res/gfx/gogeta.png");
        // Entity character2(0, 0, Blizzard);
        // character2.setcurrentFrame(0, 0, 800, 450);
        // entites2.push_back(character2);

    bool gameRunning = true;
    SDL_Event event;
    const float timeStep = 0.01f;
    float accumalator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();
    int GokuSpeed = 10;
    bool facing = true; //true = facing right
    while(gameRunning)
    {
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
                    gameRunning = false;
                if (event.type == SDL_KEYDOWN)
                {
                    if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        cout<<"v\n";
                        for (int i = 0; i < GokuSpeed; ++i)
                            GokuY++;
                    }
                    else if(event.key.keysym.sym == SDLK_UP)
                    {
                        cout<<"^\n";
                        for (int i = 0; i < GokuSpeed; ++i)
                            GokuY--;
                    }
                    else if(event.key.keysym.sym == SDLK_LEFT)
                    {
                        facing = false;
                        cout<<"<\n";
                        for (int i = 0; i < GokuSpeed; ++i)
                            GokuX--;
                    }
                    else if(event.key.keysym.sym == SDLK_RIGHT)
                    {
                        facing = true;
                        cout<<">\n";
                        for (int i = 0; i < GokuSpeed; ++i)
                            GokuX++;
                    }
                }
            }
            accumalator -= timeStep;
        } 

        //const float alpha = accumalator / timeStep;
        window.clear();
        window.render(background);
        
        if(facing)
        {
            character0.setPos(Vector2f(GokuX, GokuY));
            window.render(character0);
            
        }
        else
        {
            character0_L.setPos(Vector2f(GokuX, GokuY));
            window.render(character0_L);
            
        }
        // for (Entity& e: entites2)
        //     window.render(e);
        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if(frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}