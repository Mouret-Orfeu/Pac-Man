#pragma once

#include "Ghost.h"
#include "PacMan.h"

class GameModel {
public:
    GameModel();
    ~GameModel();

    void update(CharacterDirection input_direction);

    Ghost& getGhost();
    PacMan& getPacMan();

    int getCount() const;
    void setCount(int count);

private:
    Ghost ghost;
    PacMan pacman;
    int count;
};
