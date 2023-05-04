#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "PacMan.h"

#include <SDL.h>

class GameModel;

class Clyde : public Ghost {
public:
    Clyde(GameModel& gameModel, PacMan& pacman);
    ~Clyde();

    void leaveTheDen() override;

    void updateTargetTile() override;

    void move(int count) override;
};
