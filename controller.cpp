#include "controller.h"

controller::direction_t controller::check_input()
{      
    direction_t direction=none;

    int nbk;
    const Uint8* keys = SDL_GetKeyboardState(&nbk);

    if (keys[SDL_SCANCODE_LEFT])
        direction= direction_t::left;
    if (keys[SDL_SCANCODE_RIGHT])
        direction= direction_t::right;
    if (keys[SDL_SCANCODE_UP])
        direction= direction_t::up;
    if (keys[SDL_SCANCODE_DOWN])
        direction= direction_t::down;

    return direction;
}

void controller::check_escap(bool& quit)
{      
    int nbk;
    const Uint8* keys = SDL_GetKeyboardState(&nbk);
    if (keys[SDL_SCANCODE_ESCAPE])
        quit = true;
}