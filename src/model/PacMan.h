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
    PacMan(SDL_Point pos_center);

    ~PacMan();

    void move(int count) override;
    void setIntendedDirection(Direction direction);
private:
    Direction intended_direction;
};
