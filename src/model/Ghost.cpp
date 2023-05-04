#include "Ghost.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"

//Ghost::Ghost(GameModel& gameModel, Ghost::Type ghost_type, Position initial_position, Direction direction, Direction sprite_orientation)
//:Character(gameModel, initial_position, direction, sprite_orientation),
// ghost_type(ghost_type),
//{}

Ghost::Ghost(GameModel& gameModel, Ghost::Type ghost_type, Position initial_position, Direction direction, Tile scatter_target_tile, bool out_of_den)
:Character(gameModel, initial_position, direction),
 ghost_type(ghost_type),
 scatter_target_tile(scatter_target_tile),
 current_target_tile(scatter_target_tile),
 out_of_den_position((WINDOW_WIDTH-1)/2, 14*TILE_SIZE + (TILE_SIZE-1)/2),
 center_den_position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2)
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

void Ghost::setMode(Mode mode)
{
    ghost_mode=mode;
}

void Ghost::setCurrentTargetTile(Tile tile)
{
    current_target_tile=tile;
}

Tile Ghost::getCurrentTargetTile() const
{
    return current_target_tile;
}