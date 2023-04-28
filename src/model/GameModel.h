#pragma once

#include "Ghost.h"
#include "PacMan.h"

class GameModel {
public:
    GameModel();
    ~GameModel();

    void update(Character::Direction input_direction);

    Ghost& getGhost();
    PacMan& getPacMan();

    int getCount() const;
    void setCount(int count);

private:
    Ghost blinky;
    PacMan pacman;
    int count;
};
