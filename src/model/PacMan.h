#pragma once

#include "Character.h"


class PacMan : public Character {
public:

    /**
    * @brief Constructeur par defaut qui fait spawn pacman à sa position de départ standard et qui le fait partir sur la droite
    */
    PacMan();

    /*
    * @brief Constructeur qui permet de faire spawn pacman à une autre position 
    */
    PacMan(SDL_Point init_pos_up_left_pacman);
    
    ~PacMan();

    void move(int count) override;
    void setIntendedDirection(CharacterDirection direction);
private:
    CharacterDirection intended_direction;
};
