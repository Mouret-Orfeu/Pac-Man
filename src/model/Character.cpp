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
