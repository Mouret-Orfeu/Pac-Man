#include "PacMan.h"
#include "Character.h"

#include "GameModel.h"

#include <iostream>


PacMan::PacMan(SDL_Point pos_center)
:Character({Direction::RIGHT, pos_center, computeTilePosition(pos_center)}),
intended_direction(Direction::RIGHT)
{
    // Initialize PacMan-specific data here
}

PacMan::PacMan()
:Character({Direction::RIGHT, init_pos_center_pacman, computeTilePosition(init_pos_center_pacman)}),
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
    SDL_Point next_tile_intended = getNextTile(state.tile_position, intended_direction);

    // DEBUG
    // std::cout << "state.tile_position: (" << state.tile_position.y << ", " << state.tile_position.x << ")" << std::endl;
    // std::cout << "state.tile_position: " << static_cast<int>(GameModel::TILES[state.tile_position.y][state.tile_position.x]) << std::endl;
    // std::cout << "next_tile_intended: (" << next_tile_intended.y << ", " << next_tile_intended.x << ")" << std::endl;
    // std::cout << "next_tile_intended: " << static_cast<int>(GameModel::TILES[next_tile_intended.y][next_tile_intended.x]) << std::endl;

    if(isTileLegal(next_tile_intended) && isCenteredOnTile())
        state.direction = intended_direction;

    SDL_Point next_tile = getNextTile(state.tile_position, state.direction);
    if(!isTileLegal(next_tile_intended) && isCenteredOnTile())
        state.direction = Direction::NONE;

    //pour l'instant pacman se contente d'aller dans la direction de l'input sans rien regarder
    updatePosition();
}

void PacMan::setIntendedDirection(Direction direction) {
    // Update the direction
    intended_direction = direction;
}
