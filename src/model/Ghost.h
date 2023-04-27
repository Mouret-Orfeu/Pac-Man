#pragma once

#include "Character.h"

#include <SDL.h>

class Ghost : public Character {
public:
    Ghost(SDL_Point init_pos_up_left_ghost, SDL_Point init_pos_center_ghost);
    ~Ghost();

    void move(int count) override;
};
