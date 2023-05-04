#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "common/Tile.h"

#include <SDL.h>

class GameModel;

class Inky : public Ghost {
public:
    Inky(GameModel& gameModel);
    ~Inky();

    void updateDirection() override;

    void move(int count) override;
};
