#include "Ghost.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"

Ghost::Ghost(GameModel& gameModel, Ghost::Type ghost_type, Position initial_position, Direction direction, Direction sprite_orientation)
:Character(gameModel, initial_position, direction, sprite_orientation)
{}

Ghost::Ghost(GameModel& gameModel, Ghost::Type ghost_type, Position initial_position, Direction direction)
:Character(gameModel, initial_position, direction)
{}

Ghost::~Ghost() {
    // Clean up Ghost-specific data here
}

Ghost::Type Ghost::getType() const {
    return ghost_type;
}