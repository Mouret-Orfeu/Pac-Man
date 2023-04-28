#include "PacMan.h"
#include "Character.h"

#include "view/GameView.h"




PacMan::PacMan(SDL_Point pos_center)
:Character({Direction::RIGHT, pos_center, computeTilePosition(pos_center)}),
intended_direction(Direction::RIGHT)
{
    // Initialize PacMan-specific data here
}

PacMan::PacMan()
:Character({Direction::RIGHT, GameViewConstants::init_pos_center_pacman, computeTilePosition(init_pos_center_pacman)}),
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

    if(isTileLegal(next_tile_intended))
    {
        //if(isCenteredOnTile())
        //{
        //    state.direction = intended_direction;
        //}

        state.direction = intended_direction;

    }

    //pour l'instant pacman se contente d'aller dans la direction de l'input sans rien regarder
    updatePosition ();
}

void PacMan::setIntendedDirection(Direction direction) {
    // Update the direction
    intended_direction = direction;
}
