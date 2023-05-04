#include "Blinky.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "Ghost.h"

const Position init_pos_Blinky = Position((WINDOW_WIDTH-1)/2, 14*TILE_SIZE + (TILE_SIZE-1)/2);
const Tile scatter_target_tile_Blinky = {0,WINDOW_COLS-3};

Blinky::Blinky(GameModel& gameModel)
:Ghost(gameModel, Ghost::Type::BLINKY, init_pos_Blinky, Direction::LEFT, scatter_target_tile_Blinky)
{}

Blinky::~Blinky() {
    // Clean up Blinky-specific data here
}

void Blinky::move(int count) {
    // Update the direction based on the count value
    switch (count / 128) {
        case 0:
            direction = Direction::RIGHT;
            sprite_orientation = Direction::RIGHT;
            position.incrementX(1);
            break;
        case 1:
            direction = Direction::DOWN;
            sprite_orientation = Direction::DOWN;
            position.incrementY(1);
            break;
        case 2:
            direction = Direction::LEFT;
            sprite_orientation = Direction::LEFT;
            position.incrementX(-1);
            break;
        case 3:
            direction = Direction::UP;
            sprite_orientation = Direction::UP;
            position.incrementY(-1);
            break;
    }
}
