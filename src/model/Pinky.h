#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "PacMan.h"

#include <SDL.h>

class GameModel;

class Pinky : public Ghost {
public:
    Pinky(GameModel& game_model, PacMan&pacman);
    ~Pinky();

    Tile findChaseTargetTile();

    void leaveTheDen() override;

    void updateTargetTile() override;
};
