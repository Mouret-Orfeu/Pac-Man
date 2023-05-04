#include "Ghost.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"

Ghost::Ghost(GameModel& gameModel, Ghost::Type ghost_type, Position initial_position, Direction direction, Direction sprite_orientation)
:Character(gameModel, initial_position, direction, sprite_orientation),
 ghost_type(ghost_type)
{}

Ghost::Ghost(GameModel& gameModel, Ghost::Type ghost_type, Position initial_position, Direction direction, Tile scatter_target_tile)
:Character(gameModel, initial_position, direction),
 ghost_type(ghost_type)
{}

Ghost::~Ghost() {
    // Clean up Ghost-specific data here
}

Ghost::Type Ghost::getType() const {
    return ghost_type;
}

Ghost::Mode Ghost::getMode() const {
    return ghost_mode;
}

void Ghost::setChaseTargetTile(Tile tile)
{
    chase_target_tile=tile;
}

Tile Ghost::getScatterTargetTile() const
{
    return scatter_target_tile;
}

