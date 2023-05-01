#pragma once

#include "Ghost.h"

#include "common/Position.h"

#include <SDL.h>

class GameModel;

class Inky : public Ghost {
public:
    Inky(GameModel& gameModel);
    ~Inky();

    void move(int count) override;
};
