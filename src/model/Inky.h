#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "common/Tile.h"
#include "PacMan.h"

#include <SDL.h>

class GameModel;

class Inky : public Ghost {
public:
    Inky(GameModel& gameModel, PacMan& pacman);
    ~Inky();

    void leaveTheDen() override;

    void updateTargetTile() override;

    void move(int count) override;
};
