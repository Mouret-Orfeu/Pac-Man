#pragma once

#include "Character.h"
#include "common/Position.h"
#include "common/Direction.h"

#include <SDL.h>

class Ghost : public Character {
public:
    Ghost(Position position, Direction direction, Direction sprite_orientation);
    Ghost(Position position, Direction direction);
    virtual ~Ghost();
};
