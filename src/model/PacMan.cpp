#include "PacMan.h"
#include "Character.h"

#define TILE_SIZE 24
#define SIZE_PACMAN_SPRITE 13
#define SIZE_PACMAN_RESIZED 39


SDL_Point init_pos_up_left_pacman = { 106*3,181*3+3*TILE_SIZE };
SDL_Point init_pos_center_pacman = { 24+SIZE_PACMAN_RESIZED/2, 72+SIZE_PACMAN_RESIZED/2 };

PacMan::PacMan()
:Character({CharacterDirection::RIGHT, init_pos_up_left_pacman, init_pos_center_pacman}),
 intended_direction(CharacterDirection::RIGHT),
 sprite_r({ 473,1, SIZE_PACMAN_SPRITE ,SIZE_PACMAN_SPRITE  }),
 sprite_l({ 473,17, SIZE_PACMAN_SPRITE ,SIZE_PACMAN_SPRITE  }),
 sprite_d({ 473,49, SIZE_PACMAN_SPRITE ,SIZE_PACMAN_SPRITE  }),
 sprite_u({ 473,33, SIZE_PACMAN_SPRITE ,SIZE_PACMAN_SPRITE  })
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
