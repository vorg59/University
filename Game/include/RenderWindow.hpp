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
    int getRefreshRate();
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void clear();
    void render(Entity& p_entity, float p_mag);
    void display();
    void cleanUp();
};