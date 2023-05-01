#pragma once

#include "Ghost.h"

#include "common/Position.h"

#include <SDL.h>

class GameModel;

class Pinky : public Ghost {
public:
    Pinky(GameModel& gameModel);
    ~Pinky();

    void move(int count) override;
};
