#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Entity.hpp"
using namespace std;

class RenderWindow
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer; //OpenGL

public:
    void render(Entity& p_entity, float p_mag);
    
    int getRefreshRate();
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    static void* threadrender(void* tparam);
    void clear();
    void display();
    void cleanUp();
};