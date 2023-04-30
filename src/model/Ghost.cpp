#include "Ghost.h"
#include "common/Position.h"
#include "common/Direction.h"

Ghost::Ghost(Position position, Direction direction, Direction sprite_orientation)
:Character(position, direction, sprite_orientation)
{}

Ghost::Ghost(Position position, Direction direction)
:Character(position, direction)
{}

Ghost::~Ghost() {
    // Clean up Ghost-specific data here
}
