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
};
