#include "Ghost.h"


Ghost::Ghost()
:Character({CharacterDirection::RIGHT, {34, 34}}),
 sprite_r({ 3,123, 16,16 }),
 sprite_l({ 37,123, 16,16 }),
 sprite_d({ 105,123, 16,16 }),
 sprite_u({ 71,123, 16,16 })
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
