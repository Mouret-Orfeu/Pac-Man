#include "Ghost.h"


Ghost::Ghost()
:sprite_r({ 3,123, 16,16 }),
 sprite_l({ 37,123, 16,16 }),
 sprite_d({ 105,123, 16,16 }),
 sprite_u({ 71,123, 16,16 })
{
    // Initialize Ghost-specific data here
    state.direction = GhostDirection::RIGHT;
    state.position = { 34, 34 };
}

Ghost::~Ghost() {
    // Clean up Ghost-specific data here
}

void Ghost::updatePosition(int count) {
    // Update the direction based on the count value
    switch (count / 128) {
        case 0:
            state.direction = GhostDirection::RIGHT;
            state.position.x++;
            break;
        case 1:
            state.direction = GhostDirection::DOWN;
            state.position.y++;
            break;
        case 2:
            state.direction = GhostDirection::LEFT;
            state.position.x--;
            break;
        case 3:
            state.direction = GhostDirection::UP;
            state.position.y--;
            break;
    }
}

GhostState Ghost::getState() const {
    return state;
}

void Ghost::setState(const GhostState& state) {
    this->state = state;
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
