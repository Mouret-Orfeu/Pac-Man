#include "Character.h"

Character::Character(CharacterState state)
: state(state)
{}

Character::~Character() {}

CharacterState Character::getState() const {
    return state;
}

void Character::setState(const CharacterState& state) {
    this->state = state;
}

CharacterDirection Character::getDirection() const {
    return state.direction;
}

void Character::setDirection(CharacterDirection direction) {
    state.direction = direction;
}

SDL_Point Character::getTopLeftPosition() const{
    return state.top_left_position;
}

void Character::setTopLeftPosition(int x, int y) {
    state.top_left_position.x = x;
    state.top_left_position.y = y;
}

SDL_Point Character::getCenterPosition() const {
    return state.center_position;
}

void Character::setCenterPosition(int x, int y) {
    state.center_position.x = x;
    state.center_position.y = y;
}

SDL_Point Character::getTilePosition() const {
    return state.tile_position;
}

void Character::setTilePosition(int x, int y) {
    state.tile_position.x = x;
    state.tile_position.y = y;
}

void Character::updatePosition () {
    switch (state.direction) {
        case CharacterDirection::UP:
            state.top_left_position.y -= 1;
            state.center_position.y -= 1;
            break;
        case CharacterDirection::DOWN:
            state.top_left_position.y += 1;
            state.center_position.y += 1;
            break;
        case CharacterDirection::LEFT:
            state.top_left_position.x -= 1;
            state.center_position.x -= 1;
            break;
        case CharacterDirection::RIGHT:
            state.top_left_position.x += 1;
            state.center_position.x += 1;
            break;
        default:
            break;
    }

    state.tile_position.x = state.center_position.x/24;
    state.tile_position.y = state.center_position.y/24+3;
}
