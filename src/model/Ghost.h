#pragma once

#include "Character.h"
#include "common/Position.h"

#include <SDL.h>

class Ghost : public Character {
public:
    Ghost(Position initial_position);
    Ghost();
    ~Ghost();

    void move(int count) override;
private:
    static constexpr SDL_Point initial_position_Blinky = { 11,35 };
};
