#include <iostream>
#include "PacMan.h"
#include "Character.h"

#include "GameModel.h"




PacMan::PacMan(SDL_Point pos_center)
:Character({Direction::LEFT, pos_center, computeTilePosition(pos_center)}, Direction::LEFT),
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
    SDL_Point forward_tile = getNextTile(state.tile_position, state.direction);

    //si la nouvelle trajectoire est légale, on change la direction
    if(isTileLegal(next_tile_intended))
    {
        //if(isCenteredOnTile())
        //{
        //    state.direction = intended_direction;
        //}

        state.direction = intended_direction;
    }
    //sinon on test si la trajectoire actuelle est légale
    else
    {   
        //Si elle n'est pas légale, on ne bouge plus
        if(!isTileLegal(forward_tile))
            state.direction = Direction::NONE;
        
    }

    //pour l'instant pacman se contente d'aller dans la direction de l'input sans rien regarder
    updatePosition ();
}

void PacMan::setIntendedDirection(Direction direction) {
    // Update the direction
    intended_direction = direction;
}
