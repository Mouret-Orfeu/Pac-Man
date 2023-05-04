#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "common/Tile.h"
#include "PacMan.h"
#include <memory>

#include <SDL.h>

class GameModel;

class Inky : public Ghost {
public:
    Inky(GameModel& gameModel, PacMan& pacman, std::unique_ptr<Ghost>& blinky_uniq_ptr);
    ~Inky();

    Tile findChaseTargetTile();

    void leaveTheDen() override;

    void updateTargetTile() override;

    void move(int count) override;
private:
    std::unique_ptr<Ghost>& blinky_uniq_ptr;
};
