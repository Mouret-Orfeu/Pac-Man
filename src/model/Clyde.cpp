#include "Clyde.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "Ghost.h"

const Position init_pos_Clyde = Position((WINDOW_WIDTH-1)/2+2*TILE_SIZE, 17*TILE_SIZE + (TILE_SIZE-1)/2);
const Tile scatter_target_tile_Clyde = {WINDOW_ROWS-1,0};

Clyde::Clyde(GameModel& gameModel)
:Ghost(gameModel, Ghost::Type::CLYDE, init_pos_Clyde, Direction::UP, scatter_target_tile_Clyde)
{}

Clyde::~Clyde() {
    // Clean up Clyde-specific data here
}

void Clyde::move(int count) {
    // Update the direction based on the count value
}

void Clyde::updateDirection(){}
