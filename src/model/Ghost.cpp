#include "Ghost.h"

#define SIZE_GHOST_SPRITE 14
#define SIZE_GHOST_RESIZED 42


SDL_Point init_pos_up_left_Blinky = { 15,75 };
SDL_Point init_pos_center_Blinky = { 34+SIZE_GHOST_RESIZED/2, 34+SIZE_GHOST_RESIZED/2 };


Ghost::Ghost()
:Character({CharacterDirection::RIGHT, init_pos_up_left_Blinky, init_pos_center_Blinky}),
 sprite_r({ 457,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE }),
 sprite_l({ 489,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE }),
 sprite_d({ 553,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE }),
 sprite_u({ 521,65, SIZE_GHOST_SPRITE,SIZE_GHOST_SPRITE })
{
    // Initialize Ghost-specific data here
}

Ghost::~Ghost() {
    // Clean up Ghost-specific data here
}

void Ghost::move(int count) {
    // Update the direction based on the count value
    switch (count / 128) {
        case 0:
            state.direction = CharacterDirection::RIGHT;
            state.top_left_position.x++;
            break;
        case 1:
            state.direction = CharacterDirection::DOWN;
            state.top_left_position.y++;
            break;
        case 2:
            state.direction = CharacterDirection::LEFT;
            state.top_left_position.x--;
            break;
        case 3:
            state.direction = CharacterDirection::UP;
            state.top_left_position.y--;
            break;
    }
}

const SDL_Rect& Ghost::getSpriteR() const {
    return sprite_r;
}

const SDL_Rect& Ghost::getSpriteL() const {
    return sprite_l;
}

const SDL_Rect& Ghost::getSpriteD() const {
    return sprite_d;
}

const SDL_Rect& Ghost::getSpriteU() const {
    return sprite_u;
}
