#pragma once

#include "Ghost.h"

#include "common/Position.h"

#include <SDL.h>

class GameModel;

class Blinky : public Ghost {
public:
    Blinky(GameModel& gameModel);
    ~Blinky();

    void move(int count) override;
};
