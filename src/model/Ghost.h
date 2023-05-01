#pragma once

#include "Character.h"
#include "common/Position.h"
#include "common/Direction.h"

#include <SDL.h>

class GameModel;

class Ghost : public Character {
public:
    enum class Type {
        BLINKY,
        PINKY,
        INKY,
        CLYDE
    };

    Ghost(GameModel& gameModel, Type ghost_type, Position initial_position, Direction direction, Direction sprite_orientation);
    Ghost(GameModel& gameModel, Type ghost_type, Position initial_position, Direction direction);
    virtual ~Ghost();

    Type getType() const;

private:
    Type ghost_type;
};
