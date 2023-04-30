#pragma once

#include "Character.h"
#include "common/Position.h"
#include "common/Direction.h"

#include <SDL.h>

class GameModel;

class Ghost : public Character {
public:
    Ghost(GameModel& gameModel, Position initial_position, Direction direction, Direction sprite_orientation);
    Ghost(GameModel& gameModel, Position initial_position, Direction direction);
    virtual ~Ghost();
};
