#pragma once

#include "Ghost.h"

#include <vector>
#include <iostream>
#include <memory>

class GameModel;



class MonsterDen {
public:
    MonsterDen(GameModel& game_model);
    ~MonsterDen();

    void updateMonsterDen();

    /**
    * @brief Enregistre le type des fantomes dans la den dans un vecteur et trie ce vecteur dans l'ordre PINKY>INKY>CLYDE 
    */
    void setGhostsInDen();

    std::vector<Ghost::Type> getGhostsInDen() const;

    /**
    * @brief Incrémente le conteur de dot mangé du fantome en tête de ghost_in_den trié dans l'ordre PINKY>INKY>CLYDE
    */
    void incrementDotCounter();

    void printCounterDot(Ghost::Type ghost_type) const;

    bool getCanLeaveDen(Ghost::Type ghost_type) const;
    


private:
    GameModel& game_model;
    std::vector<Ghost::Type> ghosts_in_den;


    int count_eaten_dots_Pinky;
    int count_eaten_dots_Inky;
    int count_eaten_dots_Clyde;

    int dot_limit_pinky;
    int dot_limit_inky;
    int dot_limit_clyde;

    bool can_leave_den_Blinky;
    bool can_leave_den_Pinky;
    bool can_leave_den_Inky;
    bool can_leave_den_Clyde;
    
};
