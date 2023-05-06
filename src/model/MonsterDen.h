#pragma once

#include "Ghost.h"
#include <vector>
#include <iostream>
#include <memory>

class MonsterDen {
public:
    MonsterDen(GameModel& gameModel);
    ~MonsterDen();

    void updateMonsterDen();

    void setGhostsInDen();

private:
    GameModel& gameModel;
    std::vector<Ghost::Type> ghosts_in_den;


    int count_eaten_dots_Blinky;
    int count_eaten_dots_Pinky;
    int count_eaten_dots_Inky;
    int count_eaten_dots_Clyde;
    
};
