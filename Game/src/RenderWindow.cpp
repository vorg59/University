#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "RenderWindow.hpp"
#include "Entity.hpp"
using namespace std;

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h):window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
        cout << "Window failed to init. Error: " << SDL_GetError() << endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture == NULL)
        cout<<"Failed to load texture. Error: "<<SDL_GetError()<<endl;

    return texture;
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity, float p_mag)
{
    SDL_Rect src;
    src.x=p_entity.getcurrentFrame().x;
    src.y=p_entity.getcurrentFrame().y;
    src.w=p_entity.getcurrentFrame().w;
    src.h=p_entity.getcurrentFrame().h;

    SDL_Rect dst;
    dst.x= p_entity.getPos().x/p_mag;
    dst.y= p_entity.getPos().y/p_mag;
    dst.w=p_entity.getcurrentFrame().w*p_mag;
    dst.h=p_entity.getcurrentFrame().h*p_mag;

    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}