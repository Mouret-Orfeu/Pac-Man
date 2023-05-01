#include "Inky.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "Ghost.h"

const Position init_pos_Inky = Position((WINDOW_WIDTH-1)/2-2*TILE_SIZE, 17*TILE_SIZE + (TILE_SIZE-1)/2);

Inky::Inky(GameModel& gameModel)
:Ghost(gameModel, init_pos_Inky, Direction::UP)
{}

Inky::~Inky() {
    // Clean up Inky-specific data here
}

void Inky::move(int count) {
    // Update the direction based on the count value
}

Ghost::Type Inky::getType() const {
    return Ghost::Type::INKY;
}
