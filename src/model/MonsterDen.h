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

    void reset();

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

    int getCouterDotPacDeath() const;

    bool canLeaveDen(Ghost::Type ghost_type) const;
    


private:
    GameModel& game_model;
    std::vector<Ghost::Type> ghosts_in_den;


    int count_eaten_dots_Pinky;
    int count_eaten_dots_Inky;
    int count_eaten_dots_Clyde;

    int count_eaten_dots_after_pac_death;

    int dot_limit_pinky;
    int dot_limit_inky;
    int dot_limit_clyde;

    int dot_limit_pinky_after_pac_death;
    int dot_limit_inky_after_pac_death;
    int dot_limit_clyde_after_pac_death;

    bool can_leave_den_Blinky;
    bool can_leave_den_Pinky;
    bool can_leave_den_Inky;
    bool can_leave_den_Clyde;

    //Quand pacman meurt et respawn, la manière de compter les gommes mangées pour libérer les fantomes change
    bool mode_after_pac_death;

    //la limite après laquelle on force les fantomes à sortir quand pacman mange pas de dot (ce timer est dans game_model)
    const float limit_last_dot_eaten_timer;
    
};
