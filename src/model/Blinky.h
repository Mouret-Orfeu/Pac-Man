#pragma once

#include "Ghost.h"

#include "common/Position.h"
#include "PacMan.h"
#include "MonsterDen.h"

#include <SDL.h>

class GameModel;

class Blinky : public Ghost {
public:
    Blinky(GameModel& game_model, PacMan& pacman, MonsterDen& monster_den);
    ~Blinky();

    void reset() override;

    void leaveTheDen() override;

    void updateTargetTile() override;

    int getSpeed1() const;
    int getSpeed2() const;
    int getSpeed3() const;
    int getCurrentSpeed() const;

    void updateSpeed();

    void TimeBasedModeUpdate(float time_count, float fright_time_count, bool frightened_bool);

    void die() override;


private:
    int speed1;
    int speed2;
    int speed3;
};
