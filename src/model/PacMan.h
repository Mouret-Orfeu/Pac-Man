#pragma once

#include "Character.h"

class PacMan : public Character {
public:
    PacMan(SDL_Point init_pos_up_left_pacman, SDL_Point init_pos_center_pacman);
    ~PacMan();

    void move(int count) override;
    void setIntendedDirection(CharacterDirection direction);
private:
    CharacterDirection intended_direction;
};
