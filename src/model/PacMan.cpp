#include "PacMan.h"
#include "Character.h"

PacMan::PacMan()
:Character({CharacterDirection::RIGHT, {322, 642}}),
 intended_direction(CharacterDirection::RIGHT),
 sprite_r({ 19,89, 16,16 }),
 sprite_l({ 46,89, 16,16 }),
 sprite_d({ 108,89, 16,16 }),
 sprite_u({ 74,89, 16,16 })
{
    // Initialize PacMan-specific data here
}

PacMan::~PacMan() {
    // Clean up PacMan-specific data here
}

// Implement PacMan-specific methods here
void PacMan::updatePosition(int count) {
    (void)count;

    // Update the direction based on the intended direction
    // TODO: Check if the intended direction is valid,
    //       i.e. it doesn't point to a wall
    state.direction = intended_direction;

    switch (state.direction) {
        case CharacterDirection::LEFT:
            state.position.x--;
            break;
        case CharacterDirection::RIGHT:
            state.position.x++;
            break;
        case CharacterDirection::UP:
            state.position.y--;
            break;
        case CharacterDirection::DOWN:
            state.position.y++;
            break;
        case CharacterDirection::NONE:
            break;
    }
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
