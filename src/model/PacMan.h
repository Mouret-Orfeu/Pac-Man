#pragma once

#include "Character.h"

class PacMan : public Character {
public:
    PacMan();
    ~PacMan();

    void updatePosition(int count) override;
    void setIntendedDirection(CharacterDirection direction);
    const SDL_Rect& getSpriteR() const;
    const SDL_Rect& getSpriteL() const;
    const SDL_Rect& getSpriteD() const;
    const SDL_Rect& getSpriteU() const;
private:
    CharacterDirection intended_direction;
    const SDL_Rect sprite_r;
    const SDL_Rect sprite_l;
    const SDL_Rect sprite_d;
    const SDL_Rect sprite_u;
};
