#pragma once

#include "Ghost.h"

#include "common/Position.h"

#include <SDL.h>

class Blinky : public Ghost {
public:
    Blinky(Position initial_position);
    Blinky();
    ~Blinky();

    void move(int count) override;
};
