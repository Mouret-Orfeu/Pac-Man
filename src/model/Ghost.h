#pragma once

#include "Character.h"

#include <SDL.h>

class Ghost : public Character {
public:
    Ghost();
    ~Ghost();

    void move(int count) override;
    const SDL_Rect& getSpriteR() const;
    const SDL_Rect& getSpriteL() const;
    const SDL_Rect& getSpriteD() const;
    const SDL_Rect& getSpriteU() const;
private:
    const SDL_Rect sprite_r;
    const SDL_Rect sprite_l;
    const SDL_Rect sprite_d;
    const SDL_Rect sprite_u;
};
