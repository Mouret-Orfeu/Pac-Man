#include "PacMan.h"
#include "Character.h"


#define SIZE_PACMAN 16


SDL_Point init_pos_up_left = { 24,72 };
SDL_Point init_pos_center = { 24+SIZE_PACMAN/2, 72+SIZE_PACMAN/2 };

PacMan::PacMan()
:Character({CharacterDirection::RIGHT, init_pos_up_left, init_pos_center}),
 intended_direction(CharacterDirection::RIGHT),
 sprite_r({ 19,89, SIZE_PACMAN ,SIZE_PACMAN  }),
 sprite_l({ 46,89, SIZE_PACMAN ,SIZE_PACMAN  }),
 sprite_d({ 108,89, SIZE_PACMAN ,SIZE_PACMAN  }),
 sprite_u({ 74,89, SIZE_PACMAN ,SIZE_PACMAN  })
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

const SDL_Rect& PacMan::getSpriteR() const {
    return sprite_r;
}

const SDL_Rect& PacMan::getSpriteL() const {
    return sprite_l;
}

const SDL_Rect& PacMan::getSpriteD() const {
    return sprite_d;
}

const SDL_Rect& PacMan::getSpriteU() const {
    return sprite_u;
}
