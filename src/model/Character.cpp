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
    // TODO: use attributes of Character
    // when they are defined instead of hard-coded values
    state.top_left_position.x = x;
    state.top_left_position.y = y;
    state.center_position.x = x + 6*3;
    state.center_position.y = y + 6*3;
}

SDL_Point Character::getCenterPosition() const {
    return state.center_position;
}

void Character::setCenterPosition(int x, int y) {
    // TODO: use attributes of Character
    // when they are defined instead of hard-coded values
    state.center_position.x = x;
    state.center_position.y = y;
    state.top_left_position.x = x - 6*3;
    state.top_left_position.y = y - 6*3;
}

SDL_Point Character::getTilePosition() const {
    return { state.center_position.x/24, state.center_position.y/24+3 };
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
}
