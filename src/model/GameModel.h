#pragma once

#include "Ghost.h"

class GameModel {
public:
    GameModel();
    ~GameModel();

    void update();

    Ghost& getGhost();

    int getCount() const;
    void setCount(int count);

private:
    Ghost ghost;
    int count;
};
