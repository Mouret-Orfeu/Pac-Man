#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "PacMan.h"

#include <SDL.h>

class GameModel;

class Clyde : public Ghost {
public:
    Clyde(GameModel& game_model, PacMan& pacman);
    ~Clyde();

    Tile findChaseTargetTile();

    void leaveTheDen() override;

    void updateTargetTile() override;
};
