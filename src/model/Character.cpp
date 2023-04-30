#include "Character.h"
#include "common/Position.h"
#include "common/Direction.h"

Character::Character(Position position, Direction direction, Direction sprite_orientation)
:position(position), direction(direction), sprite_orientation(sprite_orientation)
{}

Character::Character(Position position, Direction direction)
:Character(position, direction, direction)
{}

Character::~Character() {}


Position Character::getPosition() const {
    return position;
}

Direction Character::getDirection() const {
    return direction;
}

void Character::setDirection(Direction direction) {
    this->direction = direction;
}

Direction Character::getSpriteOrientation() const {
    return sprite_orientation;
}

void Character::setSpriteOrientation(Direction sprite_orientation) {
    this->sprite_orientation = sprite_orientation;
}

void Character::updatePosition () {
    switch (direction) {
        case Direction::UP:
            position.incrementY(-1);
            break;
        case Direction::DOWN:
            position.incrementY(1);
            break;
        case Direction::LEFT:
            position.incrementX(-1);
            break;
        case Direction::RIGHT:
            position.incrementX(1);
            break;
        default:
            break;
    }
}
