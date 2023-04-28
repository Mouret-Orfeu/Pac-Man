#include "PacMan.h"
#include "Character.h"

#include "view/GameView.h"




PacMan::PacMan(SDL_Point pos_up_left)
:Character({CharacterDirection::RIGHT, pos_up_left, computeCenterPosition(pos_up_left, GameViewConstants::SIZE_PACMAN_SPRITE_RESIZED),  computeTilePosition(pos_up_left, GameViewConstants::SIZE_PACMAN_SPRITE_RESIZED)}),
intended_direction(CharacterDirection::RIGHT)
{
    // Initialize PacMan-specific data here
}

PacMan::PacMan()
:Character({CharacterDirection::RIGHT, GameViewConstants::init_pos_up_left_pacman, GameViewConstants::init_pos_center_pacman, GameViewConstants::init_pos_tile_pacman}),
 intended_direction(CharacterDirection::RIGHT) 
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
    state.direction = intended_direction;

    //pour l'instant pacman se contente d'aller dans la direction de l'input sans rien regarder
    updatePosition ();
}

void PacMan::setIntendedDirection(CharacterDirection direction) {
    // Update the direction
    intended_direction = direction;
}
