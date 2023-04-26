#pragma once

#include "Character.h"

class PacMan : public Character {
public:
    PacMan(CharacterState state);
    ~PacMan();

    void updatePosition(int count) override;
};
