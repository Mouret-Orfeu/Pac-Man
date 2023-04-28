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

    int getScore() const;
    void setScore(int score);

private:
    Ghost blinky;
    PacMan pacman;
    int count;
    int score=0;
};
