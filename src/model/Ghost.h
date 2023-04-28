#pragma once

#include "Character.h"

#include <SDL.h>

class Ghost : public Character {
public:
    Ghost(SDL_Point init_pos_center_ghost);
    Ghost();
    ~Ghost();

    void move(int count) override;
};
