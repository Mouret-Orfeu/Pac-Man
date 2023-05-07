#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "common/Tile.h"
#include "PacMan.h"
#include "MonsterDen.h"

#include <memory>

#include <SDL.h>

class GameModel;

class Inky : public Ghost {
public:
    Inky(GameModel& game_model, PacMan& pacman, std::unique_ptr<Ghost>& blinky_uniq_ptr, MonsterDen& monster_den);
    ~Inky();

    Tile findChaseTargetTile();

    void leaveTheDen() override;

    void updateTargetTile() override;
private:
    std::unique_ptr<Ghost>& blinky_uniq_ptr;
};
