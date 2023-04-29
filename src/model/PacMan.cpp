#include "PacMan.h"
#include "Character.h"

#include "GameModel.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "common/GameDimensions.h"

#include <iostream>


PacMan::PacMan()
:Character(Position((WINDOW_WIDTH-1)/2, 26*TILE_SIZE + (TILE_SIZE-1)/2), Direction::RIGHT),
 intended_direction(Direction::RIGHT)
{
    // Initialize PacMan-specific data here
}

PacMan::~PacMan() {
    // Clean up PacMan-specific data here
}

// Implement PacMan-specific methods here
void PacMan::move(int count) {
    (void)count;

    // Update the direction based on the intended direction
    // TODO: Check if the intended direction is valid,
    //       i.e. it doesn't point to a wall
    Tile next_tile_intended = position.getNextTile(intended_direction);

    // DEBUG
    // std::cout << "state.tile_position: (" << position.toTile().i << ", " << position.toTile().j << ")" << std::endl;
    // std::cout << "state.tile_position: " << static_cast<int>(GameModel::TILES_MATRIX[position.toTile().i][position.toTile().j]) << std::endl;
    // std::cout << "next_tile_intended: (" << next_tile_intended.i << ", " << next_tile_intended.j << ")" << std::endl;
    // std::cout << "next_tile_intended: " << static_cast<int>(GameModel::TILES_MATRIX[next_tile_intended.i][next_tile_intended.j]) << std::endl;

    if(Position::isTileLegal(next_tile_intended) && position.isCenteredOnTile()) {
        direction = intended_direction;
        sprite_orientation = intended_direction;
    }

    Tile next_tile = position.getNextTile(direction);
    if(!Position::isTileLegal(next_tile) && position.isCenteredOnTile())
        direction = Direction::NONE;

    //pour l'instant pacman se contente d'aller dans la direction de l'input sans rien regarder
    updatePosition();
}

void PacMan::setIntendedDirection(Direction direction) {
    // Update the direction
    intended_direction = direction;
}
