#include "Pinky.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "Ghost.h"

#include <iostream>

const Position init_pos_Pinky = Position((WINDOW_WIDTH-1)/2, 17*TILE_SIZE + (TILE_SIZE-1)/2);

Pinky::Pinky(GameModel& gameModel)
:Ghost(gameModel, Ghost::Type::PINKY, init_pos_Pinky, Direction::DOWN)
{

}

Pinky::~Pinky() {
    // Clean up Pinky-specific data here
}

void Pinky::move(int count) {
    // Update the direction based on the count value
   
}
