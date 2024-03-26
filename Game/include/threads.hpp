#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Movement.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"

class Movement; // Forward declaration

struct ThreadParamInput
{
    Movement* M;
    SDL_Event event;
};

struct ThreadParamBall
{
    Movement* M;
    Entity& B;
    Entity& P1;
    Entity& P2;
    int WW;
    int WH;
};

struct ThreadParamPaddle
{
    Movement* M;
    Entity& P;
    bool iLP;
    int WH;
};

class RenderWindow;

struct ThreadParamRender
{
    RenderWindow* R;
    Entity& E;
    float mag;
};